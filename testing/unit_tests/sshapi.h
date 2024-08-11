#ifndef SSHAPI_H
#define SSHAPI_H

#include <libssh2.h>

typedef struct {
    int session_count;
} maps;

typedef struct {
    int index;
} SSHCON;

maps *createTestMaps(void);
void destroyTestMaps(maps *conf);
SSHCON *ssh_connect(maps *conf);
int ssh_get_cnt(maps *conf);
void ssh_close_session(maps *conf, int index);
void ssh_close(maps *conf);
void addToUploadQueue(maps *conf, const char *local_file, const char *remote_file);

#endif // SSHAPI_H
