#ifndef SERVICE_INTERNAL_JAVA_H
#define SERVICE_INTERNAL_JAVA_H

#include <stdio.h>

int initialize_service();
int process_request(const char* request);
void cleanup_service();
void print_response(const char* response);

#endif // SERVICE_INTERNAL_JAVA_H
