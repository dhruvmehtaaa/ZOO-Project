#include "service_internal.h"
#include <string.h>

semid mock_getShmLockId(maps *conf, int nsems) {
    return (nsems > 0) ? (semid)nsems : (semid)-1;
}

int mock_removeShmLock(maps *conf, int nsems) {
    return (nsems >= 0) ? 0 : -1;
}

int mock_lockShm(semid id) {
    return (id > 0) ? 0 : -1;
}

int mock_unlockShm(semid id) {
    return (id > 0) ? 0 : -1;
}

char* mock_getStatus(int pid) {
    static char status[50];
    snprintf(status, sizeof(status), "Status of PID %d", pid);
    return status;
}

void test_getShmLockId(void) {
    maps conf;
    semid sem_id = mock_getShmLockId(&conf, 1);
    CU_ASSERT_EQUAL(sem_id, (semid)1);

    sem_id = mock_getShmLockId(&conf, -1);
    CU_ASSERT_EQUAL(sem_id, (semid)-1);
}

void test_removeShmLock(void) {
    maps conf;
    int result = mock_removeShmLock(&conf, 1);
    CU_ASSERT_EQUAL(result, 0);

    result = mock_removeShmLock(&conf, -1);
    CU_ASSERT_EQUAL(result, -1);
}

void test_lockShm(void) {
    semid id = 1;
    int result = mock_lockShm(id);
    CU_ASSERT_EQUAL(result, 0);

    id = -1;
    result = mock_lockShm(id);
    CU_ASSERT_EQUAL(result, -1);
}

void test_unlockShm(void) {
    semid id = 1;
    int result = mock_unlockShm(id);
    CU_ASSERT_EQUAL(result, 0);

    id = -1;
    result = mock_unlockShm(id);
    CU_ASSERT_EQUAL(result, -1);
}

void test_getStatus(void) {
    int pid = 123;
    char *status = mock_getStatus(pid);
    CU_ASSERT_STRING_EQUAL(status, "Status of PID 123");
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Service Internal Test Suite", 0, 0);
    CU_add_test(suite, "test_getShmLockId", test_getShmLockId);
    CU_add_test(suite, "test_removeShmLock", test_removeShmLock);
    CU_add_test(suite, "test_lockShm", test_lockShm);
    CU_add_test(suite, "test_unlockShm", test_unlockShm);
    CU_add_test(suite, "test_getStatus", test_getStatus);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
