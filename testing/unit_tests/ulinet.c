#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *pabyData;
    size_t nDataLen;
    size_t nDataAlloc;
} _HINTERNET;

typedef struct {
    FILE *file;
} _HINTERNET_FILE;

size_t write_data_into(const char *data, size_t size, size_t nmemb, _HINTERNET *handle) {
    size_t total_size = size * nmemb;
    handle->pabyData = (char *)malloc(total_size + 1);
    if (handle->pabyData == NULL) {
        return 0;
    }
    memcpy(handle->pabyData, data, total_size);
    handle->pabyData[total_size] = '\0';
    handle->nDataLen = total_size;
    handle->nDataAlloc = total_size + 1;
    return total_size;
}

size_t write_data_into_file(const char *data, size_t size, size_t nmemb, _HINTERNET_FILE *handle) {
    size_t total_size = size * nmemb;
    if (fwrite(data, size, nmemb, handle->file) != nmemb) {
        return 0;
    }
    return total_size;
}

size_t header_write_data(const char *data, size_t size, size_t nmemb, _HINTERNET *handle) {
    size_t total_size = size * nmemb;
    handle->pabyData = (char *)malloc(total_size + 1);
    if (handle->pabyData == NULL) {
        return 0;
    }
    memcpy(handle->pabyData, data, total_size);
    handle->pabyData[total_size] = '\0';
    handle->nDataLen = total_size;
    handle->nDataAlloc = total_size + 1;
    return total_size;
}

_HINTERNET *InternetOpen(const char *agent, int access_type, const char *proxy, const char *proxy_bypass, int flags) {
    _HINTERNET *handle = (_HINTERNET *)malloc(sizeof(_HINTERNET));
    if (handle) {
        handle->pabyData = NULL;
        handle->nDataLen = 0;
        handle->nDataAlloc = 0;
    }
    return handle;
}

void InternetCloseHandle(_HINTERNET *handle) {
    if (handle) {
        if (handle->pabyData) free(handle->pabyData);
        free(handle);
    }
}

_HINTERNET *InternetOpenUrl(_HINTERNET *handle, const char *url, const char *headers, unsigned long flags, unsigned long context, void *error) {
    return handle;
}

void test_write_data_into() {
    _HINTERNET handle = {0};
    char test_data[] = "Test data";
    size_t size = 1;
    size_t nmemb = sizeof(test_data) - 1;

    size_t result = write_data_into(test_data, size, nmemb, &handle);
    CU_ASSERT_EQUAL(result, nmemb);
    CU_ASSERT_PTR_NOT_NULL(handle.pabyData);
    CU_ASSERT_STRING_EQUAL(handle.pabyData, test_data);
    CU_ASSERT_EQUAL(handle.nDataLen, nmemb);
    CU_ASSERT_EQUAL(handle.nDataAlloc, nmemb + 1);

    free(handle.pabyData);
}

void test_write_data_into_file() {
    FILE *temp_file = tmpfile();
    _HINTERNET_FILE handle = {0};
    handle.file = temp_file;
    char test_data[] = "File test data";
    size_t size = 1;
    size_t nmemb = sizeof(test_data) - 1;

    size_t result = write_data_into_file(test_data, size, nmemb, &handle);
    CU_ASSERT_EQUAL(result, nmemb);
    
    fseek(temp_file, 0, SEEK_SET);
    char buffer[256];
    fread(buffer, 1, nmemb, temp_file);
    buffer[nmemb] = '\0';
    CU_ASSERT_STRING_EQUAL(buffer, test_data);

    fclose(temp_file);
}

void test_header_write_data() {
    _HINTERNET handle = {0};
    char header_data[] = "Set-Cookie: sessionId=abc123;";
    size_t size = 1;
    size_t nmemb = sizeof(header_data) - 1;

    size_t result = header_write_data(header_data, size, nmemb, &handle);
    CU_ASSERT_EQUAL(result, nmemb);
    CU_ASSERT_PTR_NOT_NULL(handle.pabyData);
    CU_ASSERT_STRING_EQUAL(handle.pabyData, "Set-Cookie: sessionId=abc123");

    free(handle.pabyData);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("ULINET Tests", NULL, NULL);

    CU_add_test(suite, "test_write_data_into", test_write_data_into);
    CU_add_test(suite, "test_write_data_into_file", test_write_data_into_file);
    CU_add_test(suite, "test_header_write_data", test_header_write_data);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}
