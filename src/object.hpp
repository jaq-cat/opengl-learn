#pragma once

#include <GL/glew.h>
#include <vector>

using std::vector;

class Object {
    private:
        vector<GLfloat> points;
        vector<GLfloat> colors;
        GLuint vao;
        GLuint vbo;
    public:
        Object(vector<GLfloat> points, vector<GLfloat> colors) {
            this->points = points;
            this->colors = colors;
        }

        void draw() {
        }
};
