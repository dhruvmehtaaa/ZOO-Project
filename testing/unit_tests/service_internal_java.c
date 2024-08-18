#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "service_internal_java.h"

int initialize_service() {
    printf("Service initialized successfully.\n");
    return 1;
}

int process_request(const char* request) {
    if (request == NULL) {
        return -1;
    }
    printf("Processing request: %s\n", request);
    return 0;
}

void cleanup_service() {
    printf("Service cleaned up.\n");
}

void print_response(const char* response) {
    if (response) {
        printf("Response: %s\n", response);
    }
}

void test_initialize_service(void) {
    int result = initialize_service();
    CU_ASSERT_EQUAL(result, 1);
}

void test_process_request_valid(void) {
    int result = process_request(" Request");
    CU_ASSERT_EQUAL(result, 0);
}

void test_process_request_null(void) {
    int result = process_request(NULL);
    CU_ASSERT_EQUAL(result, -1);
}

void test_cleanup_service(void) {
    cleanup_service();
    CU_PASS("Cleanup service executed without errors");
}

void test_print_response(void) {
    print_response(" Response");
    CU_PASS("print_response executed without errors");
}

int main() {
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    CU_pSuite pSuite = CU_add_suite("service_internal_java_test_suite", 0, 0);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test initialize_service", test_initialize_service)) ||
        (NULL == CU_add_test(pSuite, "test process_request (valid)", test_process_request_valid)) ||
        (NULL == CU_add_test(pSuite, "test process_request (null)", test_process_request_null)) ||
        (NULL == CU_add_test(pSuite, "test cleanup_service", test_cleanup_service)) ||
        (NULL == CU_add_test(pSuite, "test print_response", test_print_response))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
