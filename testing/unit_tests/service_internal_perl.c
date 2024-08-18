#include "service_internal_perl.h"

PerlInterpreter *my_perl;

void test_map_to_hash(void) {
    my_perl = perl_alloc();
    perl_construct(my_perl);
    
    HV *hash = newHV();
    if (hash != NULL) {
        CU_ASSERT_PTR_NOT_NULL(hash);
    }
    perl_destruct(my_perl);
    perl_free(my_perl);
}

void test_maps_to_hash(void) {
    my_perl = perl_alloc();
    perl_construct(my_perl);
    
    HV *hash_maps = newHV();
    if (hash_maps != NULL) {
        CU_ASSERT_PTR_NOT_NULL(hash_maps);
    }
    perl_destruct(my_perl);
    perl_free(my_perl);
}

void test_hash_to_map(void) {
    my_perl = perl_alloc();
    perl_construct(my_perl);
    
    HV *hash = newHV();
    if (hash != NULL) {
        CU_ASSERT_PTR_NOT_NULL(hash);
    }
    perl_destruct(my_perl);
    perl_free(my_perl);
}

int main() {
    if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

    CU_pSuite pSuite = CU_add_suite("Suite_TestServiceInternalPerl", 0, 0);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(pSuite, "test of map_to_hash", test_map_to_hash) == NULL) ||
        (CU_add_test(pSuite, "test of maps_to_hash", test_maps_to_hash) == NULL) ||
        (CU_add_test(pSuite, "test of hash_to_map", test_hash_to_map) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
