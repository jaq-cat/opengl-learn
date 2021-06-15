#pragma once
#include <GL/glew.h>

struct _s_shaders {
    char* (*load)(char *filename);
    GLuint (*compile)(const GLchar *src, GLuint type);
    GLuint (*create)(char *vrtx, char *frag);
};

extern const struct _s_shaders SHD;
