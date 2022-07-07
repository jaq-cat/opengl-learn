#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ECSJ_CONTENT(varname, type, component)\
  memcpy(&varname, component->content, sizeof(type))

typedef struct {
  unsigned int type;
  void *content;
} ecsj_component;

typedef struct {
  ecsj_component* components;
  unsigned short len;
  unsigned short __allocated;
} ecsj_entity;

ecsj_component __component(unsigned int type, void *data, unsigned long size);
ecsj_entity __entity();

#define ECSJ_ENTITY() __entity()
#define ECSJ_COMPONENT(datatype, type, data) __component(type, &data, sizeof(datatype))

void ecsj_entity_add_component(ecsj_entity *e, ecsj_component component);

bool entity_has_components(ecsj_entity *e, unsigned int types[], unsigned int types_len);

void ecsj_on_entities_with_components(ecsj_entity *entities[], unsigned int entities_len, unsigned int types[], unsigned int types_len, void (*func)(ecsj_entity* e));

ecsj_component* ecsj_get_component(ecsj_entity *e, unsigned int type);
