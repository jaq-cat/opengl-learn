#include "vbo.h"

int vbo_create(GLfloat data[], GLuint size) {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

void vbo_bind(GLuint vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void vbo_unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


const struct _s_vbo VBO = {
    vbo_create,
    vbo_bind,
    vbo_unbind,
};
