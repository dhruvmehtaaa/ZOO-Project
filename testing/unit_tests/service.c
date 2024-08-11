#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "service.h"

map* createMockMap() {
    map* newMap = (map*)malloc(sizeof(map));
    newMap->name = strdup("key");
    newMap->value = strdup("value");
    newMap->next = NULL;
    return newMap;
}

iotype* createMockIOType() {
    iotype* newIOType = (iotype*)malloc(sizeof(iotype));
    newIOType->content = createMockMap();
    newIOType->next = NULL;
    return newIOType;
}

elements* createMockElements() {
    elements* newElements = (elements*)malloc(sizeof(elements));
    newElements->name = strdup("element");
    newElements->content = createMockMap();
    newElements->metadata = createMockMap();
    newElements->format = NULL;
    newElements->defaults = createMockIOType();
    newElements->supported = createMockIOType();
    newElements->next = NULL;
    return newElements;
}

service* createMockService() {
    service* newService = (service*)malloc(sizeof(service));
    newService->content = createMockMap();
    newService->metadata = createMockMap();
    newService->inputs = createMockElements();
    newService->outputs = createMockElements();
    return newService;
}

void inheritMap(map **dest, const map *src) {
    if (src) {
        *dest = (map*)malloc(sizeof(map));
        (*dest)->name = strdup(src->name);
        (*dest)->value = strdup(src->value);
        (*dest)->next = NULL;
    }
}

void freeMap(map *m) {
    if (m) {
        free(m->name);
        free(m->value);
        free(m);
    }
}

void inheritIOType(iotype **dest, const iotype *src) {
    if (src) {
        *dest = (iotype*)malloc(sizeof(iotype));
        inheritMap(&(*dest)->content, src->content);
        (*dest)->next = NULL;
    }
}

void freeIOType(iotype *iot) {
    if (iot) {
        freeMap(iot->content);
        free(iot);
    }
}

void inheritElements(elements **dest, const elements *src) {
    if (src) {
        *dest = (elements*)malloc(sizeof(elements));
        (*dest)->name = strdup(src->name);
        inheritMap(&(*dest)->content, src->content);
        inheritMap(&(*dest)->metadata, src->metadata);
        (*dest)->format = NULL;
        inheritIOType(&(*dest)->defaults, src->defaults);
        inheritIOType(&(*dest)->supported, src->supported);
        (*dest)->next = NULL;
    }
}

void freeElements(elements *e) {
    if (e) {
        free(e->name);
        freeMap(e->content);
        freeMap(e->metadata);
        freeIOType(e->defaults);
        freeIOType(e->supported);
        free(e);
    }
}

void inheritance(registry *reg, service **s) {
    if (s && *s) {
        (*s)->content = createMockMap();
        (*s)->metadata = createMockMap();
    }
}

void freeRegistry(registry *r) {
    if (r) {
        free(r);
    }
}

void freeService(service *s) {
    if (s) {
        freeMap(s->content);
        freeMap(s->metadata);
        freeElements(s->inputs);
        freeElements(s->outputs);
        free(s);
    }
}

void test_inheritMap(void) {
    map* pmIn = createMockMap();
    map* pmOut = NULL;
    
    inheritMap(&pmOut, pmIn);
    
    CU_ASSERT_PTR_NOT_NULL(pmOut);
    CU_ASSERT_STRING_EQUAL(pmOut->value, pmIn->value);
    
    freeMap(pmIn);
    freeMap(pmOut);
}

void test_inheritIOType(void) {
    iotype* piotIn = createMockIOType();
    iotype* piotOut = NULL;
    
    inheritIOType(&piotOut, piotIn);
    
    CU_ASSERT_PTR_NOT_NULL(piotOut);
    CU_ASSERT_PTR_NOT_NULL(piotOut->content);
    CU_ASSERT_STRING_EQUAL(piotOut->content->value, piotIn->content->value);
    
    freeIOType(piotIn);
    freeIOType(piotOut);
}

void test_inheritElements(void) {
    elements* peIn = createMockElements();
    elements* peOut = NULL;
    
    inheritElements(&peOut, peIn);
    
    CU_ASSERT_PTR_NOT_NULL(peOut);
    CU_ASSERT_PTR_NOT_NULL(peOut->content);
    CU_ASSERT_PTR_NOT_NULL(peOut->metadata);
    CU_ASSERT_PTR_NOT_NULL(peOut->defaults);
    CU_ASSERT_PTR_NOT_NULL(peOut->supported);
    
    freeElements(peIn);
    freeElements(peOut);
}

void test_inheritance(void) {
    registry* prReg = (registry*)malloc(sizeof(registry));
    service* psServ = createMockService();
    
    inheritance(prReg, &psServ);
    
    CU_ASSERT_PTR_NOT_NULL(psServ);
    CU_ASSERT_PTR_NOT_NULL(psServ->content);
    CU_ASSERT_PTR_NOT_NULL(psServ->metadata);
    
    freeRegistry(prReg);
    freeService(psServ);
}

int main() {
    CU_initialize_registry();
    
    CU_pSuite suite = CU_add_suite("InheritanceSuite", NULL, NULL);
    CU_add_test(suite, "test_inheritMap", test_inheritMap);
    CU_add_test(suite, "test_inheritIOType", test_inheritIOType);
    CU_add_test(suite, "test_inheritElements", test_inheritElements);
    CU_add_test(suite, "test_inheritance", test_inheritance);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return 0;
}
