#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "service_yaml.h"

Service* create_service(int id, const char* name) {
    Service* service = (Service*)malloc(sizeof(Service));
    if (service) {
        service->id = id;
        strncpy(service->name, name, sizeof(service->name) - 1);
        service->name[sizeof(service->name) - 1] = '\0';
    }
    return service;
}

void free_service(Service* service) {
    if (service) {
        free(service);
    }
}

const char* service_to_yaml(const Service* service) {
    static char yaml_str[256];
    snprintf(yaml_str, sizeof(yaml_str), "id: %d\nname: %s\n", service->id, service->name);
    return yaml_str;
}

Service* yaml_to_service(const char* yaml_str) {
    Service* service = (Service*)malloc(sizeof(Service));
    if (service) {
        sscanf(yaml_str, "id: %d\nname: %49[^\n]", &service->id, service->name);
    }
    return service;
}

void test_create_service() {
    Service* service = create_service(1, "Test Service");
    CU_ASSERT_PTR_NOT_NULL(service);
    CU_ASSERT_EQUAL(service->id, 1);
    CU_ASSERT_STRING_EQUAL(service->name, "Test Service");
    free_service(service);
}

void test_service_to_yaml() {
    Service* service = create_service(2, "Another Service");
    const char* yaml_str = service_to_yaml(service);
    CU_ASSERT_STRING_EQUAL(yaml_str, "id: 2\nname: Another Service\n");
    free_service(service);
}

void test_yaml_to_service() {
    const char* yaml_str = "id: 3\nname: Third Service\n";
    Service* service = yaml_to_service(yaml_str);
    CU_ASSERT_PTR_NOT_NULL(service);
    CU_ASSERT_EQUAL(service->id, 3);
    CU_ASSERT_STRING_EQUAL(service->name, "Third Service");
    free_service(service);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Service YAML Suite", 0, 0);

    CU_add_test(suite, "test_create_service", test_create_service);
    CU_add_test(suite, "test_service_to_yaml", test_service_to_yaml);
    CU_add_test(suite, "test_yaml_to_service", test_yaml_to_service);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}
