#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>
#include "service_internal_r.h"

maps createMockMaps(void) {
    maps m;
    m.size = 1;
    m.content = malloc(sizeof(map));
    m.content[0].key = strdup("key1");
    m.content[0].value = strdup("value1");
    return m;
}

void freeMaps(maps *m) {
    for (size_t i = 0; i < m->size; ++i) {
        free(m->content[i].key);
        free(m->content[i].value);
    }
    free(m->content);
    m->content = NULL;
    m->size = 0;
}

void test_RList_FromMaps(void) {
    maps mockMaps = createMockMaps();
    CU_ASSERT_PTR_NOT_NULL(mockMaps.content);
    CU_ASSERT_STRING_EQUAL(mockMaps.content[0].key, "key1");
    CU_ASSERT_STRING_EQUAL(mockMaps.content[0].value, "value1");
    freeMaps(&mockMaps);
    CU_ASSERT_PTR_NULL(mockMaps.content);
}

void test_CreateEmptyMaps(void) {
    maps m;
    m.size = 0;
    m.content = NULL;
    CU_ASSERT_PTR_NULL(m.content);
    CU_ASSERT_EQUAL(m.size, 0);
}

void test_FreeAlreadyFreedMaps(void) {
    maps m;
    m.size = 1;
    m.content = malloc(sizeof(map));
    m.content[0].key = strdup("key");
    m.content[0].value = strdup("value");

    freeMaps(&m);
    CU_ASSERT_PTR_NULL(m.content);

    freeMaps(&m);
    CU_ASSERT_PTR_NULL(m.content);
}

void test_CreateMultipleMaps(void) {
    maps m;
    m.size = 2;
    m.content = malloc(2 * sizeof(map));
    m.content[0].key = strdup("key1");
    m.content[0].value = strdup("value1");
    m.content[1].key = strdup("key2");
    m.content[1].value = strdup("value2");

    CU_ASSERT_PTR_NOT_NULL(m.content);
    CU_ASSERT_STRING_EQUAL(m.content[0].key, "key1");
    CU_ASSERT_STRING_EQUAL(m.content[0].value, "value1");
    CU_ASSERT_STRING_EQUAL(m.content[1].key, "key2");
    CU_ASSERT_STRING_EQUAL(m.content[1].value, "value2");

    freeMaps(&m);
}

void test_CreateMapsWithNulls(void) {
    maps m;
    m.size = 1;
    m.content = malloc(sizeof(map));
    m.content[0].key = NULL;
    m.content[0].value = NULL;

    CU_ASSERT_PTR_NOT_NULL(m.content);
    CU_ASSERT_PTR_NULL(m.content[0].key);
    CU_ASSERT_PTR_NULL(m.content[0].value);

    freeMaps(&m);
}

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Suite", 0, 0);
    CU_add_test(pSuite, "test of RList_FromMaps", test_RList_FromMaps);
    CU_add_test(pSuite, "test of CreateEmptyMaps", test_CreateEmptyMaps);
    CU_add_test(pSuite, "test of FreeAlreadyFreedMaps", test_FreeAlreadyFreedMaps);
    CU_add_test(pSuite, "test of CreateMultipleMaps", test_CreateMultipleMaps);
    CU_add_test(pSuite, "test of CreateMapsWithNulls", test_CreateMapsWithNulls);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
