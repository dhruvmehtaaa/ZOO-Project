#ifndef ZOO_LOADER_FPM_H
#define ZOO_LOADER_FPM_H

#include <json-c/json.h>

typedef struct {
    char name[50];
    int id;
} maps;

typedef struct {
    char key[50];
    char value[50];
} map;

map* getMapFromMaps(const maps *conf, const char *section, const char *key);
int runAsyncRequest(maps **conf, map **map1, map **map2, json_object *obj);

extern map* (*mock_getMapFromMaps)(const maps*, const char*, const char*);
extern int (*mock_runAsyncRequest)(maps**, map**, map**, json_object*);

int cgiMain();
int cgiInit();

#endif // ZOO_LOADER_FPM_H
