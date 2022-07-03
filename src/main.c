#include "init.h"
#include "vao.h"
#include "vbo.h"
#include "shaders.h"
#include "objects.h"
#include <stdlib.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "ecsj/ecsj.h"
#include <SOIL2.h>

object triangle;

void myobj_start() {
}

void myobj_update() {
}

void myobj_init() {
  GLfloat positions[] = {
    // top triangle
    -1.0f, 1.0f, // top left
    1.0f,  1.0f, // top right
    1.0f,  -1.0f, // bottom right

    // bottom triangle
    1.0f,  -1.0f, // bottom right
    -1.0f,  -1.0f, // bottom left
    -1.0f,   1.0f // top left
  };

  transform t = {0, 0};
  GLuint m = vbo_create(positions, sizeof(positions));
  collider c = {0};
  triangle = obj_create(t, m, c, myobj_start, myobj_update);
}

int main() {
  GLFWwindow *win;
  int result = init(&win);
  if (result > 0) {
    fprintf(stderr, "[!] Failed to initialize ");
    switch (result) {
      case E_GLFW_INIT:
        fprintf(stderr, "GLFW");
        break;
      case E_GLFW_WIN:
        fprintf(stderr, "GLFW Window");
        break;
      case E_GLEW_INIT:
        fprintf(stderr, "GLEW");
        break;
    }
    fprintf(stderr, "\n");
    return -1;
  }

  fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));
  fprintf(stderr, "OpenGL vendor: %s\n", glGetString(GL_VENDOR));
  fprintf(stderr, "OpenGL version: %s\n", glGetString(GL_VERSION));

  myobj_init();

  ecsj_component *trivbo_c = ecsj_get_component(&triangle, Model);
  GLuint trivbo;
  memcpy(&trivbo, trivbo_c->content, sizeof(GLuint));

  // how to use positions in the shader
  vbo_bind(trivbo);
  GLuint trivao = vao_create(0, 0);
  vao_bind(trivao);
  vao_attr(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*2);

  // shaders
  char *vertex = shd_load("res/shaders/vertex.glsl");
  char *frag = shd_load("res/shaders/frag.glsl");
  GLuint shader = shd_create(vertex, frag);

  glUseProgram(shader);

  while (!glfwWindowShouldClose(win)) {
    // clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw stuff
    /*glFlush();*/

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // show stuff
    glfwSwapBuffers(win);

    glfwPollEvents();
    // close window
    if (glfwGetKey(win, GLFW_KEY_ESCAPE))
      glfwSetWindowShouldClose(win, 1);
  }
  glfwTerminate();
  return 0;
}
