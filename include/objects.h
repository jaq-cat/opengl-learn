#pragma once
#include "ecsj/ecsj.h"
#include "GL/glew.h"

typedef ecsj_entity object;

typedef struct {
  GLfloat x, y;
} transform;

typedef GLuint vbo;

typedef struct {
  char placeholder;
} collider;

typedef struct {
  void (*start)();
  void (*update)();
} methods;

typedef enum {
  Transform,
  VBO,
  Collider,
  Methods,
} component_types;

object obj_create(transform transform_data, vbo vbo_data, collider collider_data, void (*start)(), void (*update)());
