#pragma once
#include <GL/glew.h>

struct _s_vbo {
    int (*create)();
    void (*bind)(GLuint);
    void (*unbind)(GLuint);
};

extern const struct _s_vbo VBO;
