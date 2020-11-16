#include <fstream>
#include <sstream>

#include <iostream>
#include <string>
#include <string_view>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

using std::string;
using std::cout;
using std::endl;

#define WIDTH 640
#define HEIGHT 640
//#define HEIGHT 480

std::string load_file(const std::string& path) {
    auto ss = std::ostringstream{};
    std::ifstream file(path);
    ss << file.rdbuf();
    return ss.str();
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

    // configure sheet
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glLineWidth(1);

    int width, height;
    glfwGetFramebufferSize(win, &width, &height);
    glViewport(0, 0, width, height);

    // version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    cout << "Renderer: " << renderer << endl;
    cout << "OpenGL version: " << version << endl;

    // triangle
    float points[] = {
         0.0, 0.5,  0.0,
         0.5, -0.5, 0.0,
        -0.5, -0.5, 0.0
    };

    // vertices or something
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // shaders
    std::string vs_string, fs_string;
    const char* vs_c = (vs_string = load_file("shaders/vertex_shader.glsl")).c_str();
    const char* fs_c = (fs_string = load_file("shaders/fragment_shader.glsl")).c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_c, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_c, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, fs);
    glAttachShader(shader_program, vs);
    glLinkProgram(shader_program);

    // main loop
    while (!glfwWindowShouldClose(win)) {
        // update

        // draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        glBindVertexArray(vao);

        glDrawArrays(GL_LINE_LOOP, 0, 3);

        // poll events
        glfwPollEvents();

        // show stuff
        glfwSwapBuffers(win);
    }

    glfwTerminate();
    return 0;
}
