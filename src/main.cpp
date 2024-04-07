#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"

const std::string vertexShader = R"glsl(
#version 330 core
layout(location = 0) in vec4 position;

void main() {
  gl_Position = position;
}
)glsl";

const std::string fragmentShader = R"glsl(
#version 330 core
layout(location = 0) out vec4 color;

void main() {
  color = vec4(1.0, 5.0, 5.0, 5.0);
}
)glsl";

int main() {
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("semen");

  // vertices triangle
  float vertices[] = {
      -0.5f, -0.5f, 
       0.5f, -0.5f, 
       0.5f,  0.5f, 
  };

  // create VBO, manages vertices in GPU (where we then tell it how to interpret
  // the vertices)
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

  unsigned int shader = createShader(vertexShader, fragmentShader);
  glUseProgram(shader);

  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }

  return 0;
}
