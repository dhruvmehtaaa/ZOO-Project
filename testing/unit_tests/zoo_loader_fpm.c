#include "zoo_loader_fpm.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

static map* mock_getMapFromMaps_func(const maps *conf, const char *section, const char *key) {
    static map m;
    return &m;
}

static int mock_runAsyncRequest_func(maps **conf, map **map1, map **map2, json_object *obj) {
    return 0;
}

map* (*mock_getMapFromMaps)(const maps*, const char*, const char*) = mock_getMapFromMaps_func;
int (*mock_runAsyncRequest)(maps**, map**, map**, json_object*) = mock_runAsyncRequest_func;

int cgiMain() {
    return 0;
}

int cgiInit() {
    return 0;
}

void test_cgiMain() {
    CU_ASSERT_EQUAL(cgiMain(), 0);
}

void test_cgiInit() {
    CU_ASSERT_EQUAL(cgiInit(), 0);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("CGI Tests", 0, 0);
    CU_add_test(suite, "test_cgiMain", test_cgiMain);
    CU_add_test(suite, "test_cgiInit", test_cgiInit);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
