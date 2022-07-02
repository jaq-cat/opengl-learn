#pragma once
#include "ecsj/ecsj.h"
#include "GL/glew.h"

typedef ecsj_entity object;

typedef struct {
  GLfloat x, y;
} transform;

typedef struct {
  GLfloat *vertices; 
} model;

typedef struct {
  char placeholder;
} collider;

typedef struct {
  void (*start)();
  void (*update)();
} methods;

typedef enum {
  Transform,
  Model,
  Collider,
  Methods,
} component_types;
