#include "init.h"

int init(GLFWwindow **win) {
    glewExperimental = GL_TRUE;
    if (!glfwInit())
        return E_GLFW_INIT;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // no resize/decorate
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    *win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL);
    if (*win == NULL) {
        glfwTerminate();
        return E_GLFW_WIN;
    }
    glfwMakeContextCurrent(*win);

    // glew
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return E_GLEW_INIT;
    }

    glfwSetInputMode(*win, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return E_NONE;
}
