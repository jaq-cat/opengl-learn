#include <iostream>
#include <string>
#include <string_view>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>

#include "common/shaders.hpp"

using std::string;
using std::cout;
using std::cerr;
using std::endl;
using std::pair;

using namespace glm;

#define WIDTH 640.0f * 1.8f
#define HEIGHT 480.0f * 1.8f

int main(int argc, char** argv) {
    glewExperimental = GL_TRUE; // initialize glfw
    if (!glfwInit()) {
        cerr <<  "Failed to initialize GLFW" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // no resize/decorate
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing

    GLFWwindow *win = glfwCreateWindow(WIDTH, HEIGHT, "Hello, OpenGL!", NULL, NULL); // initialize window
    if (win == NULL) {
        cerr << "Failed to initialize GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    // glew
    if (glewInit() != GLEW_OK) {
        cerr << "Failed to initialzie GLEW" << endl;
        glfwTerminate();
        return -1;
    }

    // print opengl info
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);

    // vao
    GLuint vaId;
    glGenVertexArrays(1, &vaId);
    glBindVertexArray(vaId);

    // triangle
    static const GLfloat tri_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // put triangle in opengl
    GLuint vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tri_data), tri_data, GL_STATIC_DRAW);

    GLuint programId = setupShaders("src/shaders/vertex.glsl", "src/shaders/frag.glsl");

    // matrix stuff
    glm::mat4 projection = glm::perspective(45.0f, WIDTH/HEIGHT, 0.1f, 100.f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(4, 3, 3), // 4, 3, 3 in world space
        glm::vec3(0, 0, 0), // looking at 0, 0, 0
        glm::vec3(0, 1, 0)); // head up (0, -1, 0 to look upside down)

    glm::mat4 model = glm::mat4(1.0f); // identity matrix (model is at the origin)
    glm::mat4 mvp = projection * view * model;

    GLuint matrixId = glGetUniformLocation(programId, "MVP");

    // main loop
    while (!glfwWindowShouldClose(win)) {
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // shaders
        glUseProgram(programId);

        // matrix stuff
        glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

        // draw
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vb);
        glVertexAttribPointer(
            0, // attr 0
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0, // stride
            NULL // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

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
