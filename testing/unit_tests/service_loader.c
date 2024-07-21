#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <dlfcn.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../zoo-project/zoo-kernel/service.h"
#include "../../zoo-project/zoo-kernel/service_internal.h"
#include "../../zoo-project/zoo-kernel/service_internal_python.h"

static int stdout_fd;
static FILE* stdout_file;
static char stdout_buf[1024];

// Setup function to redirect stdout to a buffer
int setup(void) {
    stdout_fd = dup(fileno(stdout));
    stdout_file = freopen("/dev/null", "w", stdout);
    return (stdout_file == NULL) ? -1 : 0;
}

// Teardown function to restore stdout
int teardown(void) {
    fflush(stdout);
    dup2(stdout_fd, fileno(stdout));
    close(stdout_fd);
    return 0;
}

// Utility function to capture stdout
void capture_stdout(void) {
    fflush(stdout);
    freopen("/dev/null", "w", stdout);
    setvbuf(stdout, stdout_buf, _IOLBF, sizeof(stdout_buf));
}

// Utility function to restore stdout and print captured buffer
void restore_stdout(void) {
    fflush(stdout);
    dup2(stdout_fd, fileno(stdout));
    close(stdout_fd);
    stdout_file = fdopen(stdout_fd, "w");
    printf("%s", stdout_buf);
}

// Test function for `sigint_handler`
void test_sigint_handler(void) {
    capture_stdout();
    sigint_handler(SIGINT);
    restore_stdout();
    CU_ASSERT_STRING_EQUAL(stdout_buf, "Not this time!\n");
}

// Test function for `main` with minimal valid arguments
void test_main_valid(void) {
    char *argv[] = {"program_name", "service_name", "directory", "GetCapabilities"};
    int argc = 4;
    int result = main(argc, argv);
    CU_ASSERT_EQUAL(result, 0);
}

// Test function for `main` with invalid arguments
void test_main_invalid(void) {
    char *argv[] = {"program_name", "service_name"};
    int argc = 2;
    int result = main(argc, argv);
    CU_ASSERT_EQUAL(result, 1);
}

// Mock function for `dlopen`
void* mock_dlopen(const char* filename, int flag) {
    return (void*)1; // Mocked non-null pointer
}

// Mock function for `dlsym`
void* mock_dlsym(void* handle, const char* symbol) {
    return (void*)1; // Mocked non-null pointer
}

// Mock function for `dlclose`
int mock_dlclose(void* handle) {
    return 0; // Mocked success
}

// Test function for dynamic loading
void test_dynamic_loading(void) {
    void* (*original_dlopen)(const char*, int) = dlopen;
    void* (*original_dlsym)(void*, const char*) = dlsym;
    int (*original_dlclose)(void*) = dlclose;

    dlopen = mock_dlopen;
    dlsym = mock_dlsym;
    dlclose = mock_dlclose;

    char *argv[] = {"program_name", "service_name", "directory", "Execute", "function_name"};
    int argc = 5;
    int result = main(argc, argv);
    CU_ASSERT_EQUAL(result, 0);

    dlopen = original_dlopen;
    dlsym = original_dlsym;
    dlclose = original_dlclose;
}

int main() {
    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    // Add suite to the registry
    CU_pSuite pSuite = CU_add_suite("Suite_Service", setup, teardown);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the tests to the suite
    if ((NULL == CU_add_test(pSuite, "test of sigint_handler()", test_sigint_handler)) ||
        (NULL == CU_add_test(pSuite, "test of main() with valid arguments", test_main_valid)) ||
        (NULL == CU_add_test(pSuite, "test of main() with invalid arguments", test_main_invalid)) ||
        (NULL == CU_add_test(pSuite, "test of dynamic loading", test_dynamic_loading))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run tests using basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
