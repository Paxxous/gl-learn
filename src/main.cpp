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

  spdlog::debug("reading shaders..");
  const std::string fragmentShader = parseShader("./res/shdrs/fragmentShader.glsl");
  const std::string vertexShader = parseShader("./res/shdrs/vertexShader.glsl");

  spdlog::debug("Setting up window..");
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("semen");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };


  // compile and use shader
  unsigned int shader = createShader(vertexShader, fragmentShader);

  spdlog::debug("initing mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(0);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }


  glfwTerminate();
  return 0;
}
