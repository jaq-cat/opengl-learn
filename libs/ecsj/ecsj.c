#include "ecsj.h"
#include <stdbool.h>

#define __DEF_CALLOC 4
#define EXPAND(x) x+5

ecsj_component __component(unsigned int type, void *data, unsigned long size) {
  ecsj_component _c = (ecsj_component) {
    type,
    NULL,
  };
  _c.content = malloc(size);
  memcpy(_c.content, data, size);
  return _c;
}

ecsj_entity __entity() {
  ecsj_entity e = {
  };
  e.components = malloc(sizeof(ecsj_component) * __DEF_CALLOC);
  e.__allocated = __DEF_CALLOC;
  e.len = 0;
  return e;
}

// private
void ecsj_entity_expand(ecsj_entity *e) {
  if (e->len == e->__allocated) {
    unsigned short new_alloc = EXPAND(e->__allocated);
    e->components = realloc(e->components, sizeof(ecsj_component)*new_alloc);
    e->__allocated = new_alloc;
  }
}

// public
void ecsj_entity_add_component(ecsj_entity *e, ecsj_component component) {
  e->components[e->len] = component;
  e->len++;
  ecsj_entity_expand(e);
}

bool entity_has_components(ecsj_entity *e, unsigned int types[], unsigned int types_len) {
  bool found;
  for (int i=0; i<e->len; i++) {
    found = false;
    for (int k=0; k<types_len; k++) {
      if (e->components[i].type == types[k])
        found = true;
    }
    if (found == false) {
      return false;
    }
  }
  return true;
}

void ecsj_on_entities_with_components(ecsj_entity *entities[], unsigned int entities_len, unsigned int types[], unsigned int types_len, void (*func)(ecsj_entity* e)) {
  for (int i=0; i<entities_len; i++) {
    if (entity_has_components(entities[i], types, types_len)) {
      func(entities[i]);
    }
  }
}

ecsj_component* ecsj_get_component(ecsj_entity *e, unsigned int type) {
  for (unsigned short i=0; i<e->len; i++)
    if (e->components[i].type == type)
      return &e->components[i];
  return NULL;
}
