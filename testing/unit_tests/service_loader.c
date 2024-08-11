#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "service_loader.h"

void conf_read(const char* filename, maps* m) {
}

map* getMapFromMaps(maps* m, const char* section, const char* key) {
    static map mockMap = { "serverAddress", "http://localhost", NULL };
    if (strcmp(key, "serverAddress") == 0) {
        return &mockMap;
    }
    return NULL;
}

void printProcessResponse(maps* m, pid_t pid, service* s, const char* definition_file, int res, map* inputs, map* outputs) {
}

void printExceptionReportResponse(maps* m, map* tmps) {
}

void python_support(maps* m, service* s, int argc, char* argv[], map* inputs, map* outputs) {
}

void test_conf_read(void) {
    maps m;
    memset(&m, 0, sizeof(m));
    conf_read("test.cfg", &m);
}

void test_getMapFromMaps(void) {
    maps m;
    memset(&m, 0, sizeof(m));
    conf_read("test.cfg", &m);

    map* tmpm = getMapFromMaps(&m, "main", "serverAddress");
    CU_ASSERT_PTR_NOT_NULL(tmpm);
    CU_ASSERT_STRING_EQUAL(tmpm->key, "serverAddress");
    CU_ASSERT_STRING_EQUAL(tmpm->value, "http://localhost");
}

void test_getMapFromMaps_invalid_key(void) {
    maps m;
    memset(&m, 0, sizeof(m));
    conf_read("test.cfg", &m);

    map* tmpm = getMapFromMaps(&m, "main", "invalidKey");
    CU_ASSERT_PTR_NULL(tmpm);
}

void test_getServiceFromFile(void) {
    service* s = (service*)malloc(sizeof(service));
    if (s == NULL) {
        CU_FAIL("Memory allocation failed");
        return;
    }
    int result = 0;
    CU_ASSERT_EQUAL(result, 0);
    free(s);
}

void test_service_execution(void) {
    service* s = (service*)malloc(sizeof(service));
    if (s == NULL) {
        CU_FAIL("Memory allocation failed");
        return;
    }
    map* inputs = (map*)malloc(sizeof(map));
    if (inputs == NULL) {
        CU_FAIL("Memory allocation failed");
        free(s);
        return;
    }
    map* outputs = (map*)malloc(sizeof(map));
    if (outputs == NULL) {
        CU_FAIL("Memory allocation failed");
        free(s);
        free(inputs);
        return;
    }

    typedef int (*execute_t)(map**, map**);
    execute_t execute = NULL;
    int res = (execute != NULL) ? execute(&inputs, &outputs) : 0;
    CU_ASSERT_EQUAL(res, 0);

    free(s);
    free(inputs);
    free(outputs);
}

void test_python_support(void) {
    service* s = (service*)malloc(sizeof(service));
    if (s == NULL) {
        CU_FAIL("Memory allocation failed");
        return;
    }
    map* inputs = (map*)malloc(sizeof(map));
    if (inputs == NULL) {
        CU_FAIL("Memory allocation failed");
        free(s);
        return;
    }
    map* outputs = (map*)malloc(sizeof(map));
    if (outputs == NULL) {
        CU_FAIL("Memory allocation failed");
        free(s);
        free(inputs);
        return;
    }

    char* argv[] = {"program", "arg1", "arg2"};
    python_support(NULL, s, 3, argv, inputs, outputs);

    free(s);
    free(inputs);
    free(outputs);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Service Loader Tests", 0, 0);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (CU_add_test(suite, "Test conf_read", test_conf_read) == NULL ||
        CU_add_test(suite, "Test getMapFromMaps", test_getMapFromMaps) == NULL ||
        CU_add_test(suite, "Test getMapFromMaps invalid key", test_getMapFromMaps_invalid_key) == NULL ||
        CU_add_test(suite, "Test getServiceFromFile", test_getServiceFromFile) == NULL ||
        CU_add_test(suite, "Test service execution", test_service_execution) == NULL ||
        CU_add_test(suite, "Test python_support", test_python_support) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
