#include "objects.h"

object obj_create(transform transform_data, vbo vbo_data, collider collider_data, void (*start)(), void (*update)()) {
  object o = ECSJ_ENTITY();

  ecsj_entity_add_component(&o,
      ECSJ_COMPONENT(transform, Transform, transform_data));

  ecsj_entity_add_component(&o, 
      ECSJ_COMPONENT(vbo, VBO, vbo_data));

  ecsj_entity_add_component(&o, 
      ECSJ_COMPONENT(collider, Collider, collider_data));

  ecsj_entity_add_component(&o, 
      ECSJ_COMPONENT(methods, Methods, ((methods) {start, update})));

  return o;
}
