#pragma once
#include <GL/glew.h>

struct _s_vao {
    int (*create)();
    void (*bind)(GLuint);
    void (*unbind)();
    void (*attr)(GLuint i, GLuint n, GLenum type, GLenum normalized, GLuint stride);
};

extern const struct _s_vao VAO;
