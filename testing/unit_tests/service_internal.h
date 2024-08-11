#ifndef SERVICE_INTERNAL_H
#define SERVICE_INTERNAL_H

#include <CUnit/Basic.h>

// Define the maps structure
typedef struct {
    int example_field; // Add relevant fields here
} maps;

// Define semid as an int
typedef int semid;

// Function prototypes
semid getShmLockId(maps *conf, int nsems);
int removeShmLock(maps *conf, int nsems);
int lockShm(semid id);
int unlockShm(semid id);
char* getStatus(int pid);

#endif // SERVICE_INTERNAL_H
