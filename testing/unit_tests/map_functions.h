#ifndef MAP_FUNCTIONS_H
#define MAP_FUNCTIONS_H

typedef struct map {
    char* key;
    char* value;
} map;

typedef struct maps {
    int size;
    int capacity;
    map** array;
} maps;

maps* createMaps(const char* type);
map* createMap(const char* key, const char* value);
void addToMap(maps* m, const char* key, const char* value);
map* getMap(maps* m, const char* key);
void freeMaps(maps* m);
void handleError(maps** res, const char* replace, const char* num, const char* vvalues, const char* toCheck, map* r_inputs, map* lres);
void parseCookie(maps** conf, const char* cookie);
void parseInputHttpRequests(maps* m, const char* input);

#endif // MAP_FUNCTIONS_H
