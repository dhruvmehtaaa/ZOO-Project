#ifndef META_SQL_H
#define META_SQL_H

typedef struct {
} iotype;

typedef struct {
} maps;

typedef struct {
} map;

typedef struct {
} elements;

iotype* getIoType(const char** fields);
int fillAdditionalParameters(int iDbId, maps* conf, map** ap, const char* dref);
int fillMetadata(int iDbId, maps* conf, map** metadata, const char* dref);
int fillKeywords(int iDbId, maps* conf, map** pmContent, const char* dref);
int fillLiteralData(int iDbId, maps* conf, elements* in, const char* ltype);
int fillComplexData(int iDbId, maps* conf, elements* in, const char* ltype);
elements* extractInput(int iDbId, maps* conf);
void* fetchSql(maps* conf, int index, const char* query);
void cleanFetchSql(maps* conf, int index);

#endif // META_SQL_H
