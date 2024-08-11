#ifndef CACHING_H
#define CACHING_H

#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} map;

typedef struct {
    map **cache; 
    size_t size;
    size_t capacity;
} maps;

char *getFilenameForRequest(maps *conf, const char *request);
void cacheFile(maps *conf, const char *request, const char *mimeType, size_t size, const char *filename);
char *isInCache(maps *conf, const char *request);
int readCurrentInput(maps **m, maps **in, int *index, void **hInternet, map **error);
maps *createTestMaps(void);
void destroyTestMaps(maps *maps);
maps *createTestInputMaps(void);
void destroyTestInputMaps(maps *maps);

#endif 
