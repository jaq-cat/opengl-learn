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
        Object(vector<GLfloat> points, vector<GLfloat> colors, size_t i) {
            this->points = points;
            this->colors = colors;

            // vao
            glGenVertexArrays(sizeof(vao) / sizeof(GLuint), &vao);
            glBindVertexArray(vao);
            
            // vbo
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof((GLuint *) (&points[0])), &points[0], GL_STATIC_DRAW);
            glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(i);
        }

        void draw() {
        }
};
