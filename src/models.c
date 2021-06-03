#include "models.h"

model createmodel(GLfloat vertices[], GLuint vertexcount) {
    model mdl = {};
    glGenVertexArrays(1, &mdl.vao);

    // bind VAO
    glBindVertexArray(mdl.vao);

    // put position data
    putdata(&mdl, 0, vertices, vertexcount);

    // unbind VAO
    glBindVertexArray(0);

    return mdl;
}

void putdata(model *mdl, int i, GLfloat data[], GLuint vertexcount) {
    GLuint vbo;
    glGenBuffers(0, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexcount, data, GL_STATIC_DRAW);
    glVertexAttribPointer(
        i,
        3, // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0, // stride
        0 // array buffer offset
    );

    // unbind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
