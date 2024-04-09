#version 330 core
layout (location = 0) in vec3 aPos;

// i have no fucking clue how all this works but i dont give three
// flying fucks right now.

// I'm going to styl shit my way and say that it is my code.
void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
