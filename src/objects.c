#include "objects.h"

object obj_create(transform transform_data, model model_data, collider collider_data, void (*start)(), void (*update)()) {
  object o = ECSJ_ENTITY();

  ecsj_entity_add_component(&o,
      ECSJ_COMPONENT(transform, Transform, transform_data));

  ecsj_entity_add_component(&o, 
      ECSJ_COMPONENT(model, Model, model_data));

  ecsj_entity_add_component(&o, 
      ECSJ_COMPONENT(collider, Collider, collider_data));

  ecsj_entity_add_component(&o, 
      ECSJ_COMPONENT(methods, Methods, ((methods) {start, update})));

  return o;
}
