#ifndef SERVICE_LOADER_H
#define SERVICE_LOADER_H

#include <stddef.h>
#include <sys/types.h>

#define MAP_SIZE 1024
#define TIME_SIZE 256
#define ELEMENTS_SIZE 128

typedef struct map {
    char* key;
    char* value;
    struct map* next;
} map;

typedef struct maps {
    map* head;
} maps;

typedef struct service {
    char* name;
} service;

void conf_read(const char* filename, maps* m);
map* getMapFromMaps(maps* m, const char* section, const char* key);
void printProcessResponse(maps* m, pid_t pid, service* s, const char* definition_file, int res, map* inputs, map* outputs);
void printExceptionReportResponse(maps* m, map* tmps);
void python_support(maps* m, service* s, int argc, char* argv[], map* inputs, map* outputs);

#endif // SERVICE_LOADER_H
