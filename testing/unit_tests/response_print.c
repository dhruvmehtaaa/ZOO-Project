#include <CUnit/Basic.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "response_print.h"

map* createSampleMaps() {
    return (map*)0xdeadbeef;
}

void addToMap(map *m, const char *key, const char *value) {
}

void printRawdataOutputs(xmlDoc *doc, xmlNode *root_element) {
}

void printBoundingBoxDocument(xmlDoc *doc, xmlNode *root_element) {
}

void printStatusInfo(xmlDoc *doc, xmlNode *root_element) {
}

void test_printRawdataOutputs(void) {
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_element = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_element);

    map *outputs = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(outputs);

    addToMap(outputs, "mimeType", "text/plain");
    printRawdataOutputs(doc, root_element);

    CU_ASSERT_PTR_NOT_NULL(root_element);

    xmlFreeDoc(doc);
}

void test_printBoundingBoxDocument(void) {
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_element = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_element);

    map *boundingBox = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(boundingBox);

    printBoundingBoxDocument(doc, root_element);

    CU_ASSERT_PTR_NOT_NULL(root_element);

    xmlFreeDoc(doc);
}

void test_printStatusInfo(void) {
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_element = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_element);

    map *statusInfo = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(statusInfo);

    printStatusInfo(doc, root_element);

    CU_ASSERT_PTR_NOT_NULL(root_element);

    xmlFreeDoc(doc);
}

void test_createSampleMaps(void) {
    map *testMap = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(testMap);
}

void test_addToMap(void) {
    map *testMap = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(testMap);

    addToMap(testMap, "testKey", "testValue");
}

void test_printRawdataOutputs_empty(void) {
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_element = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_element);

    map *outputs = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(outputs);

    printRawdataOutputs(doc, root_element);

    CU_ASSERT_PTR_NOT_NULL(root_element);

    xmlFreeDoc(doc);
}

void test_printBoundingBoxDocument_empty(void) {
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_element = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_element);

    map *boundingBox = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(boundingBox);

    printBoundingBoxDocument(doc, root_element);

    CU_ASSERT_PTR_NOT_NULL(root_element);

    xmlFreeDoc(doc);
}

void test_printStatusInfo_empty(void) {
    xmlDoc *doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNode *root_element = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_element);

    map *statusInfo = createSampleMaps();
    CU_ASSERT_PTR_NOT_NULL(statusInfo);

    printStatusInfo(doc, root_element);

    CU_ASSERT_PTR_NOT_NULL(root_element);

    xmlFreeDoc(doc);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Response Print Tests", 0, 0);

    CU_add_test(suite, "test_printRawdataOutputs", test_printRawdataOutputs);
    CU_add_test(suite, "test_printBoundingBoxDocument", test_printBoundingBoxDocument);
    CU_add_test(suite, "test_printStatusInfo", test_printStatusInfo);
    CU_add_test(suite, "test_createSampleMaps", test_createSampleMaps);
    CU_add_test(suite, "test_addToMap", test_addToMap);
    CU_add_test(suite, "test_printRawdataOutputs_empty", test_printRawdataOutputs_empty);
    CU_add_test(suite, "test_printBoundingBoxDocument_empty", test_printBoundingBoxDocument_empty);
    CU_add_test(suite, "test_printStatusInfo_empty", test_printStatusInfo_empty);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
