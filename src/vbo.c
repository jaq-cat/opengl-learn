#include "vbo.h"

int create(GLfloat data[], int size) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    /*glBindBuffer(GL_ARRAY_BUFFER, 0);*/

    return vbo;
}

void bind(GLuint vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


const struct _s_vbo VBO = {
    create,
    bind,
    unbind,
};
