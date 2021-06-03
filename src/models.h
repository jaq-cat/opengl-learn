#pragma once
#include <GL/glew.h>

typedef struct model {
    GLuint vao;
    GLuint vertices;
} model;

model createmodel(GLfloat vertices[], GLuint vertexcount);
void putdata(model* mdl, int i, float data[], GLuint vertexcount);
