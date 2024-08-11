#ifndef SERVER_INTERNAL_H
#define SERVER_INTERNAL_H

#include <CUnit/Basic.h>

int runGetStatus(void);
int removeSubdirectory(const char* path);
int runDismiss(void);
int readServiceFile(const char* filename);
int createRegistry(void);
char* produceErrorMessage(int errorCode);
char* getMapsAsKVP(void);

#endif // SERVER_INTERNAL_H
