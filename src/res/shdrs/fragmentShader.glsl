#version 330 core
out vec4 FragColor;

// all i know is that a fragment shader runs every pixel.
// and a vertex shader like does something to the vertices given.
void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
} 
