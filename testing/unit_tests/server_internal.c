#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../zoo-project/zoo-kernel/service.h"

// Function prototypes
void test_zoo_path_compare();
void test_getVersionId();
void test_get_uuid();
void test_parseIdentifier();
void test_from_hex();
void test_to_hex();
void test_url_encode();
void test_url_decode();
void test_isValidLang();
void test_getEncoding();
void test_getVersion();
void test_readGeneratedFile();
void test_writeFile();
void test_dumpMapsValuesToFiles();

// Function to test zoo_path_compare
void test_zoo_path_compare() {
    // Test with NULL paths
    CU_ASSERT_EQUAL(zoo_path_compare(NULL, NULL), -1);
    CU_ASSERT_EQUAL(zoo_path_compare(NULL, "path"), -1);
    CU_ASSERT_EQUAL(zoo_path_compare("path", NULL), -1);

    // Test with identical paths
    CU_ASSERT_EQUAL(zoo_path_compare("/home/user/file", "/home/user/file"), 0);

    // Test with different paths
    CU_ASSERT_NOT_EQUAL(zoo_path_compare("/home/user/file1", "/home/user/file2"), 0);
}

// Function to test getVersionId
void test_getVersionId() {
    // Test with version 1.0.0
    CU_ASSERT_EQUAL(getVersionId("1.0.0"), 0);

    // Test with version 2.0.0
    CU_ASSERT_EQUAL(getVersionId("2.0.0"), 1);

    // Test with invalid version
    CU_ASSERT_EQUAL(getVersionId("3.0.0"), -1);
}

// Function to test get_uuid
void test_get_uuid() {
    char* uuid = get_uuid();
    // UUID should be 36 characters long
    CU_ASSERT_EQUAL(strlen(uuid), 36);

    // UUID should contain hyphens at specific positions
    CU_ASSERT_EQUAL(uuid[8], '-');
    CU_ASSERT_EQUAL(uuid[13], '-');
    CU_ASSERT_EQUAL(uuid[18], '-');
    CU_ASSERT_EQUAL(uuid[23], '-');

    free(uuid);
}

// Function to test parseIdentifier
void test_parseIdentifier() {
    maps* conf = createMaps();
    char buffer[256];
    parseIdentifier(conf, "/home/user", "OTB.BandMath", buffer);

    // Check if buffer is correct
    CU_ASSERT_STRING_EQUAL(buffer, "/home/user/OTB/BandMath.zcfg");

    freeMaps(conf);
}

// Function to test from_hex
void test_from_hex() {
    CU_ASSERT_EQUAL(from_hex('0'), 0);
    CU_ASSERT_EQUAL(from_hex('9'), 9);
    CU_ASSERT_EQUAL(from_hex('a'), 10);
    CU_ASSERT_EQUAL(from_hex('f'), 15);
}

// Function to test to_hex
void test_to_hex() {
    CU_ASSERT_EQUAL(to_hex(0), '0');
    CU_ASSERT_EQUAL(to_hex(9), '9');
    CU_ASSERT_EQUAL(to_hex(10), 'a');
    CU_ASSERT_EQUAL(to_hex(15), 'f');
}

// Function to test url_encode
void test_url_encode() {
    char* encoded = url_encode("test string");
    CU_ASSERT_STRING_EQUAL(encoded, "test%20string");
    free(encoded);

    encoded = url_encode("special&chars#test");
    CU_ASSERT_STRING_EQUAL(encoded, "special%26chars%23test");
    free(encoded);
}

// Function to test url_decode
void test_url_decode() {
    char* decoded = url_decode("test%20string");
    CU_ASSERT_STRING_EQUAL(decoded, "test string");
    free(decoded);

    decoded = url_decode("special%26chars%23test");
    CU_ASSERT_STRING_EQUAL(decoded, "special&chars#test");
    free(decoded);
}

// Function to test isValidLang
void test_isValidLang() {
    maps* conf = createMaps();
    setMapInMaps(conf, "main", "language", "en,fr");

    CU_ASSERT_EQUAL(isValidLang(conf, "en"), 1);
    CU_ASSERT_EQUAL(isValidLang(conf, "fr"), 1);
    CU_ASSERT_EQUAL(isValidLang(conf, "de"), -1);

    freeMaps(conf);
}

// Function to test getEncoding
void test_getEncoding() {
    maps* m = createMaps();
    addToMap(m->content, "encoding", "ISO-8859-1");

    CU_ASSERT_STRING_EQUAL(getEncoding(m), "ISO-8859-1");
    CU_ASSERT_STRING_EQUAL(getEncoding(NULL), "UTF-8");

    freeMaps(m);
}

// Function to test getVersion
void test_getVersion() {
    maps* m = createMaps();
    addToMap(m->content, "version", "2.0.0");

    CU_ASSERT_STRING_EQUAL(getVersion(m), "2.0.0");
    CU_ASSERT_STRING_EQUAL(getVersion(NULL), "1.0.0");

    freeMaps(m);
}

// Function to test readGeneratedFile
void test_readGeneratedFile() {
    maps* m = createMaps();
    map* content = createMap("value", "");

    // Write a temporary file
    FILE* file = fopen("temp.txt", "w");
    fprintf(file, "Test content");
    fclose(file);

    readGeneratedFile(m, content, "temp.txt");
    CU_ASSERT_STRING_EQUAL(getMap(content, "value")->value, "Test content");

    remove("temp.txt");
    freeMaps(m);
    free(content);
}

// Function to test writeFile
void test_writeFile() {
    char* content = "Test write content";
    CU_ASSERT_EQUAL(writeFile("test.txt", content, strlen(content)), 1);

    // Verify the content of the file
    FILE* file = fopen("test.txt", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);
    CU_ASSERT_STRING_EQUAL(buffer, "Test write content");
    fclose(file);

    remove("test.txt");
}

// Function to test dumpMapsValuesToFiles
void test_dumpMapsValuesToFiles() {
    maps* main_conf = createMaps();
    maps* in = createMaps();

    // Set temporary paths
    addToMap(main_conf->content, "tmpPath", "/tmp");
    addToMap(main_conf->content, "tmpUrl", "http://localhost/tmp");

    // Add input data
    map* input_content = createMap("value", "Input data");
    addToMap(input_content, "mimeType", "text/plain");
    in->content = input_content;

    dumpMapsValuesToFiles(&main_conf, &in);

    // Check if the file was created
    CU_ASSERT_TRUE(access("/tmp/Input_data.txt", F_OK) != -1);

    remove("/tmp/Input_data.txt");
    freeMaps(main_conf);
    freeMaps(in);
}

int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Create a test suite
    CU_pSuite suite = CU_add_suite("Service JSON Test Suite", 0, 0);
    if (NULL == suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add tests to the suite
    if ((NULL == CU_add_test(suite, "test_zoo_path_compare", test_zoo_path_compare)) ||
        (NULL == CU_add_test(suite, "test_getVersionId", test_getVersionId)) ||
        (NULL == CU_add_test(suite, "test_get_uuid", test_get_uuid)) ||
        (NULL == CU_add_test(suite, "test_parseIdentifier", test_parseIdentifier)) ||
        (NULL == CU_add_test(suite, "test_from_hex", test_from_hex)) ||
        (NULL == CU_add_test(suite, "test_to_hex", test_to_hex)) ||
        (NULL == CU_add_test(suite, "test_url_encode", test_url_encode)) ||
        (NULL == CU_add_test(suite, "test_url_decode", test_url_decode)) ||
        (NULL == CU_add_test(suite, "test_isValidLang", test_isValidLang)) ||
        (NULL == CU_add_test(suite, "test_getEncoding", test_getEncoding)) ||
        (NULL == CU_add_test(suite, "test_getVersion", test_getVersion)) ||
        (NULL == CU_add_test(suite, "test_readGeneratedFile", test_readGeneratedFile)) ||
        (NULL == CU_add_test(suite, "test_writeFile", test_writeFile)) ||
        (NULL == CU_add_test(suite, "test_dumpMapsValuesToFiles", test_dumpMapsValuesToFiles))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Clean up registry
    CU_cleanup_registry();
    return CU_get_error();
}
