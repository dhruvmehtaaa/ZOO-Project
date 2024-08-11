#ifndef SERVICE_INTERNAL_PYTHON_H
#define SERVICE_INTERNAL_PYTHON_H

#include <Python.h> 

typedef struct {
    int id;
    char* name;
} maps;

int zoo_python_support(maps** main_conf, maps* request, maps* s, maps** real_inputs, maps** real_outputs);
void PythonZooReport(maps** main_conf, const char* module, int load);


#endif // SERVICE_INTERNAL_PYTHON_H
