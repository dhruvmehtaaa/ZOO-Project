#include "caching.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <CUnit/Basic.h>

char *getFilenameForRequest(maps *conf, const char *request) {
    char *filename = malloc(256);
    snprintf(filename, 256, "%s.txt", request);
    return filename;
}

void cacheFile(maps *conf, const char *request, const char *mimeType, size_t size, const char *filename) {
    if (conf->size >= conf->capacity) {
        conf->capacity *= 2;
        conf->cache = realloc(conf->cache, conf->capacity * sizeof(map *));
    }

    map *newMap = malloc(sizeof(map));
    newMap->key = strdup(request);
    newMap->value = strdup(filename);

    conf->cache[conf->size++] = newMap;
}

char *isInCache(maps *conf, const char *request) {
    for (size_t i = 0; i < conf->size; ++i) {
        if (strcmp(conf->cache[i]->key, request) == 0) {
            return strdup(conf->cache[i]->value);
        }
    }
    return NULL;
}

int readCurrentInput(maps **m, maps **in, int *index, void **hInternet, map **error) {
    return 0;
}

maps *createTestMaps(void) {
    maps *newMaps = malloc(sizeof(maps));
    newMaps->size = 0;
    newMaps->capacity = 10;
    newMaps->cache = malloc(newMaps->capacity * sizeof(map *));
    return newMaps;
}

void destroyTestMaps(maps *maps) {
    for (size_t i = 0; i < maps->size; ++i) {
        free(maps->cache[i]->key);
        free(maps->cache[i]->value);
        free(maps->cache[i]);
    }
    free(maps->cache);
    free(maps);
}

maps *createTestInputMaps(void) {
    return createTestMaps();
}

void destroyTestInputMaps(maps *maps) {
    destroyTestMaps(maps);
}

void test_getFilenameForRequest(void) {
    maps *conf = createTestMaps();
    const char *request = "test_request";
    char *filename = getFilenameForRequest(conf, request);
    CU_ASSERT_STRING_EQUAL(filename, "test_request.txt");
    free(filename);
    destroyTestMaps(conf);
}

void test_cacheFile(void) {
    maps *conf = createTestMaps();
    const char *request = "test_request";
    const char *mimeType = "text/plain";
    const char *filename = "testfile.txt";
    cacheFile(conf, request, mimeType, strlen("test content"), filename);

    char *cachedFilename = isInCache(conf, request);
    CU_ASSERT_STRING_EQUAL(cachedFilename, "testfile.txt");

    free(cachedFilename);
    destroyTestMaps(conf);
}

void test_isInCache(void) {
    maps *conf = createTestMaps();
    const char *request = "test_request";
    const char *filename = "testfile.txt";
    cacheFile(conf, request, "text/plain", strlen("test content"), filename);

    char *cachedFilename = isInCache(conf, request);
    CU_ASSERT_STRING_EQUAL(cachedFilename, "testfile.txt");

    free(cachedFilename);
    destroyTestMaps(conf);
}

void test_readCurrentInput(void) {
    maps *m = createTestMaps();
    maps *in = createTestInputMaps();
    int index = 0;
    void *hInternet = NULL;
    map *error = NULL;
    CU_ASSERT_EQUAL(readCurrentInput(&m, &in, &index, &hInternet, &error), 0);
    destroyTestInputMaps(in);
    destroyTestMaps(m);
}

int setup(void) {
    return 0;
}

int teardown(void) {
    return 0;
}

int main(void) {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Caching Suite", setup, teardown);
    CU_add_test(suite, "test_getFilenameForRequest", test_getFilenameForRequest);
    CU_add_test(suite, "test_cacheFile", test_cacheFile);
    CU_add_test(suite, "test_isInCache", test_isInCache);
    CU_add_test(suite, "test_readCurrentInput", test_readCurrentInput);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
