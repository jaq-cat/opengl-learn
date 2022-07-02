#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "conf.h"

enum ERORRS {
    E_NONE = 0,
    E_GLFW_INIT,
    E_GLFW_WIN,
    E_GLEW_INIT,
};

int init();
