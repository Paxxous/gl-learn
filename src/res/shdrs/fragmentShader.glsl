#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main() {
  FragColor = mix(
    texture(tex2, TexCoord),
    texture(tex1, TexCoord) * vec4(ourColor, 1.0),
    0.5
  );

  // FragColor = texture(tex1, TexCoord) *  vec4(ourColor, 1.0);
  // FragColor = texture(tex2, TexCoord) *  vec4(ourColor, 1.0);
}
