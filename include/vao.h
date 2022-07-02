#pragma once
#include <GL/glew.h>

int vao_create(GLfloat data[], GLuint size);
void vao_bind(GLuint);
void vao_unbind();
void vao_attr(GLuint i, GLuint n, GLenum type, GLenum normalized, GLuint stride);
