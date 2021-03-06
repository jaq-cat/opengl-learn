#pragma once

#include <GL/glew.h>

GLuint createObject(const GLfloat vb_data[], const int vb_data_sizeof);
void drawObject(const GLfloat objSize, const GLuint objId, const GLuint matrixId, const GLfloat *objMvp);
void useColors(const GLuint colorId);
