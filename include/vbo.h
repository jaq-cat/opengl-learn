#pragma once
#include <GL/glew.h>

int vbo_create(GLfloat data[], GLuint size, GLenum usage);
void vbo_bind(GLuint);
void vbo_unbind();
