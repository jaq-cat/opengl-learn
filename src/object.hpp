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
        Object(GLfloat *points, size_t points_size, GLfloat *colors, size_t colors_size) {
            this->points = points;
            this->colors = colors;
            this->points_size = points_size;
            this->colors_size = colors_size;

            // vaos
            glGenVertexArrays(sizeof(vao) / sizeof(GLuint), &vao);
            glBindVertexArray(vao);
            
            // points vbo
            glGenBuffers(2, vbos);
            glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
            glBufferData(GL_ARRAY_BUFFER, points_size, points, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); // bind this to index 0
            glEnableVertexAttribArray(0); // enable (shaders)

            // colors vbo
            glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
            glBufferData(GL_ARRAY_BUFFER, colors_size, colors, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL); // bind this to index 1
            glEnableVertexAttribArray(1); // enable (shaders)
        }

        void draw() {
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, (points_size / sizeof(GLfloat)) / 3);
        }
};
