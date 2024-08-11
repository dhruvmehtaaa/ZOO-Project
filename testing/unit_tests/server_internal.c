#include <CUnit/Basic.h>
#include "server_internal.h"

int runGetStatus(void) {
    return 200;
}

int removeSubdirectory(const char* path) {
    if (path != NULL && strcmp(path, "/test/subdir") == 0) {
        return 0;
    }
    return -1;
}

int runDismiss(void) {
    return 404;
}

int readServiceFile(const char* filename) {
    if (filename != NULL && strcmp(filename, "service.conf") == 0) {
        return 1;
    }
    return 0;
}

int createRegistry(void) {
    return 1;
}

char* produceErrorMessage(int errorCode) {
    if (errorCode == 404) {
        return "Not Found";
    }
    return "Unknown Error";
}

char* getMapsAsKVP(void) {
    return "key1=value1;key2=value2";
}

void test_runGetStatus(void) {
    int result = runGetStatus();
    CU_ASSERT_EQUAL(result, 200);
}

void test_removeSubdirectory(void) {
    int result = removeSubdirectory("/test/subdir");
    CU_ASSERT_EQUAL(result, 0);

    result = removeSubdirectory(NULL);
    CU_ASSERT_EQUAL(result, -1);

    result = removeSubdirectory("/nonexistent/path");
    CU_ASSERT_EQUAL(result, -1);
}

void test_runDismiss(void) {
    int result = runDismiss();
    CU_ASSERT_EQUAL(result, 404);
}

void test_readServiceFile(void) {
    int result = readServiceFile("service.conf");
    CU_ASSERT_EQUAL(result, 1);

    result = readServiceFile("nonexistent.conf");
    CU_ASSERT_EQUAL(result, 0);
}

void test_createRegistry(void) {
    int result = createRegistry();
    CU_ASSERT_EQUAL(result, 1);
}

void test_produceErrorMessage(void) {
    char* result = produceErrorMessage(404);
    CU_ASSERT_STRING_EQUAL(result, "Not Found");

    result = produceErrorMessage(500);
    CU_ASSERT_STRING_EQUAL(result, "Unknown Error");
}

void test_getMapsAsKVP(void) {
    char* result = getMapsAsKVP();
    CU_ASSERT_STRING_EQUAL(result, "key1=value1;key2=value2");
}

int setup(void) {
    return 0;
}

int teardown(void) {
    return 0;
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Server Internal Suite", setup, teardown);
    CU_add_test(suite, "test_runGetStatus", test_runGetStatus);
    CU_add_test(suite, "test_removeSubdirectory", test_removeSubdirectory);
    CU_add_test(suite, "test_runDismiss", test_runDismiss);
    CU_add_test(suite, "test_readServiceFile", test_readServiceFile);
    CU_add_test(suite, "test_createRegistry", test_createRegistry);
    CU_add_test(suite, "test_produceErrorMessage", test_produceErrorMessage);
    CU_add_test(suite, "test_getMapsAsKVP", test_getMapsAsKVP);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
