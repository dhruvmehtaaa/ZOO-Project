#include <stdlib.h>
#include <CUnit/Basic.h>
#include "map_functions.h"

void test_handleError() {
    maps* test_map = NULL;
    map* map1 = createMap("key1", "value1");
    map* map2 = createMap("key2", "value2");

    handleError(&test_map, "replace", "num", "vvalues", "toCheck", map1, map2);

    CU_ASSERT_PTR_NOT_NULL(test_map);
    CU_ASSERT_PTR_NOT_NULL(getMap(test_map, "key1"));
    CU_ASSERT_PTR_NOT_NULL(getMap(test_map, "key2"));

    freeMaps(test_map);
    free(map1->key);
    free(map1->value);
    free(map1);
    free(map2->key);
    free(map2->value);
    free(map2);
}

void test_parseCookie() {
    maps* conf = NULL;
    const char* cookie = "cookie_value";

    parseCookie(&conf, cookie);

    CU_ASSERT_PTR_NOT_NULL(conf);
    CU_ASSERT_PTR_NOT_NULL(getMap(conf, "dummy_key"));

    freeMaps(conf);
}

void test_parseCookie_with_empty_cookie() {
    maps* conf = NULL;
    const char* cookie = "";

    parseCookie(&conf, cookie);

    CU_ASSERT_PTR_NOT_NULL(conf);
    CU_ASSERT_PTR_NOT_NULL(getMap(conf, "dummy_key"));

    freeMaps(conf);
}

void test_parseInputHttpRequests() {
    maps* m = createMaps("test_type");
    const char* input = "http_request_input";

    parseInputHttpRequests(m, input);

    CU_ASSERT_PTR_NOT_NULL(m);
    CU_ASSERT_PTR_NOT_NULL(getMap(m, "dummy_key"));

    freeMaps(m);
}

void test_parseInputHttpRequests_with_no_href() {
    maps* m = createMaps("test_type");
    const char* input = "http_request_input_without_href";

    parseInputHttpRequests(m, input);

    CU_ASSERT_PTR_NOT_NULL(m);
    CU_ASSERT_PTR_NOT_NULL(getMap(m, "dummy_key"));

    freeMaps(m);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Request Parser Test Suite", 0, 0);
    CU_add_test(suite, "test_handleError", test_handleError);
    CU_add_test(suite, "test_parseCookie", test_parseCookie);
    CU_add_test(suite, "test_parseCookie_with_empty_cookie", test_parseCookie_with_empty_cookie);
    CU_add_test(suite, "test_parseInputHttpRequests", test_parseInputHttpRequests);
    CU_add_test(suite, "test_parseInputHttpRequests_with_no_href", test_parseInputHttpRequests_with_no_href);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
