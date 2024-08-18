#ifndef SERVICE_INTERNAL_PERL_H
#define SERVICE_INTERNAL_PERL_H

#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>
#include <CUnit/Basic.h>

void test_map_to_hash(void);
void test_maps_to_hash(void);
void test_hash_to_map(void);

#endif // SERVICE_INTERNAL_PERL_H
