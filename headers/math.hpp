#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

using glm::mat4x4;
using glm::vec3;

void doStuff() {
    mat4x4 t = glm::identity<mat4x4>();
    mat4x4 trans = glm::translate(t, vec3(0, 2, 2));
}
