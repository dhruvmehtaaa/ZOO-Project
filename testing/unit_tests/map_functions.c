#include <stdlib.h>
#include <string.h>
#include "map_functions.h"

static void resizeMaps(maps* m);

maps* createMaps(const char* type) {
    maps* m = (maps*)malloc(sizeof(maps));
    m->size = 0;
    m->capacity = 10;
    m->array = (map**)malloc(m->capacity * sizeof(map*));
    return m;
}

map* createMap(const char* key, const char* value) {
    map* m = (map*)malloc(sizeof(map));
    m->key = strdup(key);
    m->value = strdup(value);
    return m;
}

void addToMap(maps* m, const char* key, const char* value) {
    if (m->size == m->capacity) {
        resizeMaps(m);
    }
    map* new_map = createMap(key, value);
    m->array[m->size++] = new_map;
}

map* getMap(maps* m, const char* key) {
    for (int i = 0; i < m->size; i++) {
        if (strcmp(m->array[i]->key, key) == 0) {
            return m->array[i];
        }
    }
    return NULL;
}

void freeMaps(maps* m) {
    for (int i = 0; i < m->size; i++) {
        free(m->array[i]->key);
        free(m->array[i]->value);
        free(m->array[i]);
    }
    free(m->array);
    free(m);
}

static void resizeMaps(maps* m) {
    m->capacity *= 2;
    m->array = realloc(m->array, m->capacity * sizeof(map*));
}

void handleError(maps** res, const char* replace, const char* num, const char* vvalues, const char* toCheck, map* r_inputs, map* lres) {
    if (*res == NULL) {
        *res = createMaps("default");
    }
    addToMap(*res, "key1", "value1");
    addToMap(*res, "key2", "value2");
}

void parseCookie(maps** conf, const char* cookie) {
    *conf = createMaps("cookie_type");
    addToMap(*conf, "dummy_key", "dummy_value");
}

void parseInputHttpRequests(maps* m, const char* input) {
    addToMap(m, "dummy_key", "dummy_value");
}
