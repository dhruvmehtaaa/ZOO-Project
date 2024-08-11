#ifndef SERVICE_JSON_H
#define SERVICE_JSON_H

#include <stdbool.h>

typedef struct {
    int id;
    char name[50];
} maps;

typedef struct {
    int id;
    char value[50];
} map;

bool serviceIsFilter(maps*, char*);
char* jsonToMaps(const char*);
char* jsonToMap(const char*);
char* mapToJson(map*);
char* mapsToJson(maps*);
char* serviceToJson(maps*);
char* printLiteralValueJ(const char*);
char* printGetCapabilitiesForProcessJ(const char*);
char* parseJRequest(const char*);
char* printJResult(const char*);

#endif // SERVICE_JSON_H
