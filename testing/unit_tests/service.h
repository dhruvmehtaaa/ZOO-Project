#ifndef SERVICE_H
#define SERVICE_H

#include <stdlib.h>

typedef struct map {
    char *name;
    char *value;
    struct map *next;
} map;

typedef struct iotype {
    map *content;
    struct iotype *next;
} iotype;

typedef struct elements {
    char *name;
    map *content;
    map *metadata;
    char *format;
    iotype *defaults;
    iotype *supported;
    struct elements *next;
} elements;

typedef struct service {
    map *content;
    map *metadata;
    elements *inputs;
    elements *outputs;
} service;

typedef struct registry {
} registry;

void inheritMap(map **dest, const map *src);
void freeMap(map *m);

void inheritIOType(iotype **dest, const iotype *src);
void freeIOType(iotype *iot);

void inheritElements(elements **dest, const elements *src);
void freeElements(elements *e);

void inheritance(registry *reg, service **s);
void freeRegistry(registry *r);
void freeService(service *s);

#ifdef __cplusplus
extern "C" {
#endif

int cgiMain(void);

#ifdef __cplusplus
}
#endif

#endif // SERVICE_H
