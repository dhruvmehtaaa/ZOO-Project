#include <CUnit/Basic.h>
#include <json-c/json.h>
#include "../../zoo-project/zoo-kernel/service.h"

void test_jsonToMaps_valid(void) {
    const char *str = "{\"key1\": {\"subkey1\": \"value1\"}, \"key2\": {\"subkey2\": \"value2\"}}";
    json_object *jobj = json_tokener_parse(str);
    maps *result = jsonToMaps(jobj);
    
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result->name, "key1");
    CU_ASSERT_STRING_EQUAL(result->content->name, "subkey1");
    CU_ASSERT_STRING_EQUAL(result->content->value, "value1");
    
    result = result->next;
    CU_ASSERT_STRING_EQUAL(result->name, "key2");
    CU_ASSERT_STRING_EQUAL(result->content->name, "subkey2");
    CU_ASSERT_STRING_EQUAL(result->content->value, "value2");

    json_object_put(jobj);
    freeMaps(&result);
}

void test_jsonToMaps_invalid(void) {
    const char *str = "{\"key1\": \"value1\", \"key2\": [\"value2\"]}";
    json_object *jobj = json_tokener_parse(str);
    maps *result = jsonToMaps(jobj);
    
    CU_ASSERT_PTR_NULL(result);
    
    json_object_put(jobj);
}

void test_jsonToMap_valid(void) {
    const char *str = "{\"key1\": \"value1\", \"key2\": \"value2\"}";
    json_object *jobj = json_tokener_parse(str);
    map *result = jsonToMap(jobj);
    
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_STRING_EQUAL(result->name, "key1");
    CU_ASSERT_STRING_EQUAL(result->value, "value1");
    
    result = result->next;
    CU_ASSERT_STRING_EQUAL(result->name, "key2");
    CU_ASSERT_STRING_EQUAL(result->value, "value2");
    
    json_object_put(jobj);
    freeMap(&result);
}

void test_jsonToMap_invalid(void) {
    const char *str = "[\"key1\", \"value1\"]";
    json_object *jobj = json_tokener_parse(str);
    map *result = jsonToMap(jobj);
    
    CU_ASSERT_PTR_NULL(result);
    
    json_object_put(jobj);
}

void test_mapToJson_valid(void) {
    map *myMap = createMap("key1", "value1");
    addToMap(myMap, "key2", "value2");
    json_object *jobj = mapToJson(myMap);
    
    CU_ASSERT_PTR_NOT_NULL(jobj);
    CU_ASSERT_STRING_EQUAL(json_object_get_string(json_object_object_get(jobj, "key1")), "value1");
    CU_ASSERT_STRING_EQUAL(json_object_get_string(json_object_object_get(jobj, "key2")), "value2");
    
    json_object_put(jobj);
    freeMap(&myMap);
}

void test_mapToJson_empty(void) {
    map *myMap = NULL;
    json_object *jobj = mapToJson(myMap);
    
    CU_ASSERT_PTR_NULL(jobj);
}

void test_mapsToJson_valid(void) {
    maps *myMaps = createMaps("key1");
    map *subMap = createMap("subkey1", "value1");
    addMapToMap(&(myMaps->content), subMap);
    json_object *jobj = mapsToJson(myMaps);
    
    CU_ASSERT_PTR_NOT_NULL(jobj);
    json_object *subj = json_object_object_get(jobj, "key1");
    CU_ASSERT_PTR_NOT_NULL(subj);
    CU_ASSERT_STRING_EQUAL(json_object_get_string(json_object_object_get(subj, "subkey1")), "value1");
    
    json_object_put(jobj);
    freeMaps(&myMaps);
}

void test_mapsToJson_empty(void) {
    maps *myMaps = NULL;
    json_object *jobj = mapsToJson(myMaps);
    
    CU_ASSERT_PTR_NULL(jobj);
}

void test_elementsToJson_valid(void) {
    elements *myElements = createElements("elem1");
    map *contentMap = createMap("key1", "value1");
    myElements->content = contentMap;
    json_object *jobj = elementsToJson(myElements);
    
    CU_ASSERT_PTR_NOT_NULL(jobj);
    json_object *elem = json_object_object_get(jobj, "elem1");
    CU_ASSERT_PTR_NOT_NULL(elem);
    CU_ASSERT_STRING_EQUAL(json_object_get_string(json_object_object_get(json_object_object_get(elem, "content"), "key1")), "value1");
    
    json_object_put(jobj);
    freeElements(&myElements);
}

void test_elementsToJson_empty(void) {
    elements *myElements = NULL;
    json_object *jobj = elementsToJson(myElements);
    
    CU_ASSERT_PTR_NULL(jobj);
}

void test_serviceToJson_valid(void) {
    service *myService = createService("service1");
    myService->content = createMap("key1", "value1");
    json_object *jobj = serviceToJson(myService);
    
    CU_ASSERT_PTR_NOT_NULL(jobj);
    CU_ASSERT_STRING_EQUAL(json_object_get_string(json_object_object_get(jobj, "name")), "service1");
    CU_ASSERT_STRING_EQUAL(json_object_get_string(json_object_object_get(json_object_object_get(jobj, "content"), "key1")), "value1");
    
    json_object_put(jobj);
    freeService(&myService);
}

void test_serviceToJson_empty(void) {
    service *myService = NULL;
    json_object *jobj = serviceToJson(myService);
    
    CU_ASSERT_PTR_NULL(jobj);
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite_Service", 0, 0);
    CU_add_test(suite, "test of jsonToMaps() valid input", test_jsonToMaps_valid);
    CU_add_test(suite, "test of jsonToMaps() invalid input", test_jsonToMaps_invalid);
    CU_add_test(suite, "test of jsonToMap() valid input", test_jsonToMap_valid);
    CU_add_test(suite, "test of jsonToMap() invalid input", test_jsonToMap_invalid);
    CU_add_test(suite, "test of mapToJson() valid input", test_mapToJson_valid);
    CU_add_test(suite, "test of mapToJson() empty input", test_mapToJson_empty);
    CU_add_test(suite, "test of mapsToJson() valid input", test_mapsToJson_valid);
    CU_add_test(suite, "test of mapsToJson() empty input", test_mapsToJson_empty);
    CU_add_test(suite, "test of elementsToJson() valid input", test_elementsToJson_valid);
    CU_add_test(suite, "test of elementsToJson() empty input", test_elementsToJson_empty);
    CU_add_test(suite, "test of serviceToJson() valid input", test_serviceToJson_valid);
    CU_add_test(suite, "test of serviceToJson() empty input", test_serviceToJson_empty);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
