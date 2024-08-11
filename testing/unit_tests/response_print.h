#ifndef RESPONSE_PRINT_H
#define RESPONSE_PRINT_H

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

typedef struct map map;  

map* createSampleMaps();
void addToMap(map *m, const char *key, const char *value);
void printRawdataOutputs(xmlDoc *doc, xmlNode *root_element);
void printBoundingBoxDocument(xmlDoc *doc, xmlNode *root_element);
void printStatusInfo(xmlDoc *doc, xmlNode *root_element);

#endif // RESPONSE_PRINT_H
