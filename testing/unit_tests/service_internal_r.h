#ifndef SERVICE_INTERNAL_R_H
#define SERVICE_INTERNAL_R_H

#include <stdlib.h>

typedef struct {
    char *key;
    char *value;
} map;

typedef struct {
    map *content;
    size_t size;
} maps;

maps createMockMaps(void);
void freeMaps(maps *m);

#endif // SERVICE_INTERNAL_R_H
