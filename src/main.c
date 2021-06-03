#include <stdio.h>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "conf.h"

int main() {
    glewExperimental = GL_TRUE;
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // no resize/decorate
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    GLFWwindow *win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL);
    if (win == NULL) {
        fprintf(stderr, "Failed to initialize GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    // glew
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialzie GLEW\n");
        glfwTerminate();
        return -1;
    }

    // print opengl info
    fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));
    fprintf(stderr, "OpenGL vendor: %s\n", glGetString(GL_VENDOR));
    fprintf(stderr, "OpenGL version: %s\n", glGetString(GL_VERSION));

    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(win)) {
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw objects
        glFlush();
        glfwPollEvents();

        // show stuff
        glfwSwapBuffers(win);

        // close window
        if (glfwGetKey(win, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(win, 1);
    }

    glfwTerminate();
    return 0;
}
