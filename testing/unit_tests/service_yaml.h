#ifndef SERVICE_YAML_H
#define SERVICE_YAML_H

#include <yaml.h>

typedef struct {
    int id;
    char name[50];
} Service;

Service* create_service(int id, const char* name);
void free_service(Service* service);
const char* service_to_yaml(const Service* service);
Service* yaml_to_service(const char* yaml_str);

#endif // SERVICE_YAML_H
