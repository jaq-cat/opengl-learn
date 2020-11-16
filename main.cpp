#include <iostream>
#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include "math_3d.hpp"

#define WIDTH 640
#define HEIGHT 640
//#define HEIGHT 480

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // black opaque background
    glClear(GL_COLOR_BUFFER_BIT); // clear color buffer
    glEnd();

    glFlush(); // render
}

int main(int argc, char** argv) {
    // initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return -1;
    }
    GLFWwindow* win;

    // initialize window
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL);
    if (!win) {
        fprintf(stderr, "Failed to initialize GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    // extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    // only draw closer values
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);

    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version: %s\n", version);

    glfwTerminate();
    return 0;
}
