#define GLFW_INCLUDE_NONE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"


int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("project version: {}", VERSION);

  const std::string fragmentShader = parseShader("./res/shdrs/fragmentShader.glsl");
  const std::string vertexShader = parseShader("./res/shdrs/vertexShader.glsl");

  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("semen");

  // vertices triangle
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  unsigned int VBO;
  glGenBuffers(1, &VBO);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
  glEnableVertexAttribArray(0);

  // LATER


  // compile and use shader
  unsigned int shader = createShader(vertexShader, fragmentShader);

  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }

  return 0;
}
