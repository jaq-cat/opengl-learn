#pragma once
#include <GL/glew.h>

char* shd_load(char *filename);
GLuint shd_compile(const GLchar *src, GLuint type);
GLuint shd_create(char *vrtx, char *frag);
