#include "sshapi.h"
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

maps *createTestMaps(void) {
    maps *conf = (maps *)malloc(sizeof(maps));
    if (conf) {
        conf->session_count = 0;
    }
    return conf;
}

void destroyTestMaps(maps *conf) {
    if (conf) {
        free(conf);
    }
}

SSHCON *ssh_connect(maps *conf) {
    SSHCON *ssh = (SSHCON *)malloc(sizeof(SSHCON));
    if (ssh) {
        ssh->index = 0;
    }
    return ssh;
}

int ssh_get_cnt(maps *conf) {
    return conf ? conf->session_count : 0;
}

void ssh_close_session(maps *conf, int index) {
    if (conf) {
    }
}

void ssh_close(maps *conf) {
    if (conf) {
    }
}

void addToUploadQueue(maps *conf, const char *local_file, const char *remote_file) {
}

int test_setup(void) {
    return 0;
}

int test_teardown(void) {
    return 0;
}

void test_ssh_connect(void) {
    maps *test_conf = createTestMaps();
    CU_ASSERT_PTR_NOT_NULL(test_conf);
    
    SSHCON *ssh = ssh_connect(test_conf);
    CU_ASSERT_PTR_NOT_NULL(ssh);
    
    ssh_close(test_conf);
    destroyTestMaps(test_conf);
}

void test_ssh_get_cnt(void) {
    maps *test_conf = createTestMaps();
    CU_ASSERT_PTR_NOT_NULL(test_conf);
    
    int count = ssh_get_cnt(test_conf);
    CU_ASSERT_EQUAL(count, 0);
    
    destroyTestMaps(test_conf);
}

void test_addToUploadQueue(void) {
    maps *test_conf = createTestMaps();
    CU_ASSERT_PTR_NOT_NULL(test_conf);
    
    addToUploadQueue(test_conf, "/local/path/to/file", "/remote/path/to/file");
    
    destroyTestMaps(test_conf);
}

int main(void) {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("SSHAPI Test Suite", test_setup, test_teardown);
    CU_add_test(suite, "test_ssh_connect", test_ssh_connect);
    CU_add_test(suite, "test_ssh_get_cnt", test_ssh_get_cnt);
    CU_add_test(suite, "test_addToUploadQueue", test_addToUploadQueue);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}
