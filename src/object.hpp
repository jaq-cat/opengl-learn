#pragma once

#include <GL/glew.h>
#include <vector>

using std::vector;

class Object {
    private:
        GLfloat *points;
        size_t points_size;
        GLfloat *colors;
        size_t colors_size;
        GLuint vao;
        GLuint vbos[2] = {0, 0};
    public:
        Object(GLfloat *points, size_t points_size, GLfloat *colors, size_t colors_size);
        void draw();
};
