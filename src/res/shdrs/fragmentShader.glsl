#version 330 core

out vec4 color;

in vec4 clr;
in vec2 texpos;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
  color = mix(texture(tex1, texpos),
    texture(tex2, (texpos * 2)), 0.2) * clr;
}
