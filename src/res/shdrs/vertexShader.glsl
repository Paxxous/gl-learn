#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 texturepos;

out vec4 clr;
out vec2 texpos;

void main() {
  gl_Position = vec4(pos, 1.0);
  clr = vec4(col, 1.0);
  texpos = texturepos;
}
