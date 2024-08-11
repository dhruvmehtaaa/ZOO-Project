#ifndef SQLAPI_H
#define SQLAPI_H

#include <gdal/ogr_api.h>  

typedef struct {
    OGRLayerH* layers;  
    int num_layers;
} maps;

OGRLayerH fetchSql(maps* conf, int index, const char* sql);

#endif // SQLAPI_H
