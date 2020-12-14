#include <iostream>
#include <string>
#include <string_view>
#include "../headers/util.hpp"
#include "../headers/init.hpp"
#include "../headers/object.hpp"
#include "../headers/math.hpp"

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using std::string;
using std::cout;
using std::endl;
using std::pair;

#define WIDTH 640*1.8
//#define HEIGHT 640
#define HEIGHT 480*1.8

int main(int argc, char** argv) {
    // initialize GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW");
        return -1;
    }
    GLFWwindow *win;

    // initialize window
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
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
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;

    // shape A
    GLfloat a_points[] = {
        -0.3,  0.8,  0.0, // top left
         0.3,  0.8,  0.0, // top right
        -0.6, -0.1, 0.0, // bottom left
         0.6, -0.1, 0.0, // bottom right
         0.0, -0.9, 0.0, // bottom
    };
    GLfloat a_colors[] = {
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, // RGB instead of XYZ
        0.0, 1.0, 1.0,
        0.0, 1.0, 1.0,
        0.0, 0.0, 1.0
    };
    Object obj_a(a_points, sizeof(a_points), a_colors, sizeof(a_colors));

    // obj B
    GLfloat b_points[] = {
        -0.5,  1.5, 0.0, // top left
         0.5,  1.5, 0.0, // top right
        -0.5,  1.0, 0.0, // bottom right
         0.5,  1.0, 0.0, // bottom left
    };
    GLfloat b_colors[] = {
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 1.0, 0.0,
    };
    Object obj_b(b_points, sizeof(b_points), b_colors, sizeof(b_colors));

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
        obj_a.draw();
        obj_b.draw();

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
