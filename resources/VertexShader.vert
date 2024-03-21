#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec4 color;
out vec4 tcolor;

void main() {
  gl_Position = vec4(aPos, 1.0);
  tcolor = color;
}