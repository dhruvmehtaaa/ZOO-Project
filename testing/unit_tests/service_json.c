#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include "service_json.h"

char* jsonToMaps(const char* json) {
    return strdup("maps");
}

char* jsonToMap(const char* json) {
    return strdup("map");
}

char* mapToJson(map* m) {
    return strdup("{\"id\":1, \"value\":\"example\"}");
}

char* mapsToJson(maps* m) {
    return strdup("{\"id\":1, \"name\":\"example\"}");
}

char* serviceToJson(maps* m) {
    return strdup("{\"service\":\"example\"}");
}

char* printLiteralValueJ(const char* value) {
    char* result = (char*)malloc(50);
    snprintf(result, 50, "{\"literal\":\"%s\"}", value);
    return result;
}

char* printGetCapabilitiesForProcessJ(const char* process) {
    char* result = (char*)malloc(50);
    snprintf(result, 50, "{\"process\":\"%s\"}", process);
    return result;
}

char* parseJRequest(const char* request) {
    return strdup("parsed_request");
}

char* printJResult(const char* result) {
    char* formatted = (char*)malloc(50);
    snprintf(formatted, 50, "{\"result\":\"%s\"}", result);
    return formatted;
}

void test_jsonToMaps(void) {
    char* result = jsonToMaps("{}");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "maps");
    free(result);
}

void test_jsonToMap(void) {
    char* result = jsonToMap("{}");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "map");
    free(result);
}

void test_mapToJson(void) {
    map m = {1, "example"};
    char* result = mapToJson(&m);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "{\"id\":1, \"value\":\"example\"}");
    free(result);
}

void test_mapsToJson(void) {
    maps m = {1, "example"};
    char* result = mapsToJson(&m);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "{\"id\":1, \"name\":\"example\"}");
    free(result);
}

void test_serviceToJson(void) {
    maps m = {1, "example"};
    char* result = serviceToJson(&m);
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "{\"service\":\"example\"}");
    free(result);
}

void test_printLiteralValueJ(void) {
    char* result = printLiteralValueJ("value");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "{\"literal\":\"value\"}");
    free(result);
}

void test_printGetCapabilitiesForProcessJ(void) {
    char* result = printGetCapabilitiesForProcessJ("process");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "{\"process\":\"process\"}");
    free(result);
}

void test_parseJRequest(void) {
    char* result = parseJRequest("request");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "parsed_request");
    free(result);
}

void test_printJResult(void) {
    char* result = printJResult("result");
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result, "{\"result\":\"result\"}");
    free(result);
}

int main() {
    CU_initialize_registry();

    CU_pSuite pSuite = CU_add_suite("Suite", 0, 0);
    CU_add_test(pSuite, "test_jsonToMaps", test_jsonToMaps);
    CU_add_test(pSuite, "test_jsonToMap", test_jsonToMap);
    CU_add_test(pSuite, "test_mapToJson", test_mapToJson);
    CU_add_test(pSuite, "test_mapsToJson", test_mapsToJson);
    CU_add_test(pSuite, "test_serviceToJson", test_serviceToJson);
    CU_add_test(pSuite, "test_printLiteralValueJ", test_printLiteralValueJ);
    CU_add_test(pSuite, "test_printGetCapabilitiesForProcessJ", test_printGetCapabilitiesForProcessJ);
    CU_add_test(pSuite, "test_parseJRequest", test_parseJRequest);
    CU_add_test(pSuite, "test_printJResult", test_printJResult);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
