#pragma once
#include <GL/glew.h>

int vao_create();
void vao_bind(GLuint vao);
void vao_unbind();
void vao_enable(GLuint i);
void vao_disable(GLuint i);
void vao_attr(GLuint i, GLuint n, GLenum type, GLenum normalized, GLuint stride);
