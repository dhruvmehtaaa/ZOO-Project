#include "service_internal_python.h"
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int zoo_python_support(maps** main_conf, maps* request, maps* s, maps** real_inputs, maps** real_outputs) {
    if (main_conf == NULL || *main_conf == NULL || request == NULL || s == NULL || real_inputs == NULL || real_outputs == NULL) {
        return -1;
    }
    *real_inputs = request;
    *real_outputs = s;
    return 0;
}

void PythonZooReport(maps** main_conf, const char* module, int load) {
    if (main_conf == NULL || *main_conf == NULL || module == NULL) {
        fprintf(stderr, "Invalid arguments to PythonZooReport\n");
        return;
    }
    printf("Reporting on module: %s with load: %d\n", module, load);
}

void test_zoo_python_support_valid(void) {
    maps main_conf = {0, "main_conf"};
    maps request = {1, "request_name"};
    maps s = {2, "service_name"};
    maps* real_inputs = NULL;
    maps* real_outputs = NULL;

    maps* main_conf_ptr = &main_conf;

    CU_ASSERT_EQUAL(zoo_python_support(&main_conf_ptr, &request, &s, &real_inputs, &real_outputs), 0);
    CU_ASSERT_PTR_NOT_NULL(real_inputs);
    CU_ASSERT_PTR_NOT_NULL(real_outputs);
    CU_ASSERT_PTR_EQUAL(real_inputs, &request);
    CU_ASSERT_PTR_EQUAL(real_outputs, &s);
    CU_ASSERT_EQUAL(request.id, real_inputs->id);
    CU_ASSERT_EQUAL(s.id, real_outputs->id);
    CU_ASSERT_STRING_EQUAL(request.name, real_inputs->name);
    CU_ASSERT_STRING_EQUAL(s.name, real_outputs->name);
    CU_ASSERT_STRING_EQUAL(main_conf.name, "main_conf");
}

void test_zoo_python_support_invalid(void) {
    maps* main_conf = NULL;
    maps* request = NULL;
    maps* s = NULL;
    maps* real_inputs = NULL;
    maps* real_outputs = NULL;

    CU_ASSERT_EQUAL(zoo_python_support(&main_conf, request, s, &real_inputs, &real_outputs), -1);
    CU_ASSERT_PTR_NULL(real_inputs);
    CU_ASSERT_PTR_NULL(real_outputs);
}

void test_PythonZooReport_valid(void) {
    maps main_conf = {1, "config_name"};
    maps* main_conf_ptr = &main_conf;
    const char* module = "example_module";
    int load = 10;

    PythonZooReport(&main_conf_ptr, module, load);
}

void test_PythonZooReport_invalid(void) {
    maps* main_conf = NULL;
    const char* module = "example_module";
    int load = 10;

    PythonZooReport(&main_conf, module, load);
}

void test_PythonZooReport_null_module(void) {
    maps main_conf = {1, "config_name"};
    maps* main_conf_ptr = &main_conf;
    const char* module = NULL;
    int load = 10;

    PythonZooReport(&main_conf_ptr, module, load);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("ServiceInternalPythonTestSuite", 0, 0);

    CU_add_test(suite, "test_zoo_python_support_valid", test_zoo_python_support_valid);
    CU_add_test(suite, "test_zoo_python_support_invalid", test_zoo_python_support_invalid);
    CU_add_test(suite, "test_PythonZooReport_valid", test_PythonZooReport_valid);
    CU_add_test(suite, "test_PythonZooReport_invalid", test_PythonZooReport_invalid);
    CU_add_test(suite, "test_PythonZooReport_null_module", test_PythonZooReport_null_module);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
