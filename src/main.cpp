#include <iostream>
#include <string>
#include <string_view>
#include <cmath>
#include "util.hpp"
#include "init.hpp"

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using std::string;
using std::cout;
using std::endl;
using std::pair;

#define WIDTH 640*2
//#define HEIGHT 640
#define HEIGHT 480*2

int main(int argc, char** argv) {
    // initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return -1;
    }
    GLFWwindow* win;

    // initialize window
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 8);
    win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL);
    if (!win) {
        fprintf(stderr, "Failed to initialize GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    // GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    // configuration
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glDepthFunc(GL_LESS);
    glLineWidth(1);

    // print opengl info
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL version: " << glGetString(GL_RENDERER)<< endl;

    // shape
    GLfloat points[] = {
        - 0.3,  0.8,  0.0, // top left
          0.3,  0.8,  0.0, // top right
         -0.6, -0.1, 0.0, // bottom left
          0.6, -0.1, 0.0, // bottom right
          0.0, -0.9, 0.0, // bottom
    };
    GLfloat colors[] = {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, // RGB instead of XYZ
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 0.0, 1.0
    };
    GLuint vao;
    makeObject(points, sizeof(points), colors, sizeof(colors), vao);

    GLuint shader_program;
    makeShaders(shader_program);
    // main loop
    while (!glfwWindowShouldClose(win)) {
        // update

        // draw
        glClearColor(0.0, 0.05, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw points
        glUseProgram(shader_program);
        glBindVertexArray(vao); // switch to points VAO
        glDrawArrays(GL_TRIANGLE_STRIP, 0, sizeof(points) / sizeof(GLfloat)); // draw points VAO

        // floosh
        glFlush();

        // poll events
        glfwPollEvents();

        // show stuff
        glfwSwapBuffers(win);
        if (glfwGetKey(win, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(win, 1);
        }
    }

    glfwTerminate();
    return 0;
}
