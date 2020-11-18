#version 400

layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcol;

out vec3 color;

void main() {
    color = vcol;
    gl_Position = vec4(vpos, 2.0);
}
