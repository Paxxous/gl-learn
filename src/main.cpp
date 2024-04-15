#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
// #include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"

// https://docs.gl/
int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("project vrsn: {}", VERSION);

  spdlog::debug("Setting up window..");
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("window");

  float vertices[] = {
    0.0f, 0.5f,
    -0.5f, -0.5f,
    0.5f, -0.5f
  };

  // compile and link shaders
  Shader shdr = Shader(
    "./res/shdrs/vertexShader.glsl",
    "./res/shdrs/fragmentShader.glsl"
  );

  // create VAO
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // allocate mem and upload vertices to gpu
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // tell gpu how to parse vertices
  unsigned int vert_array_index = 0;
  glVertexAttribPointer(vert_array_index, 2, GL_FLOAT, GL_FALSE,
      0 /* or you can 3 * sizeof(float), but it tightly packed */,
      0 /* or nullptr? */);
  glEnableVertexAttribArray(vert_array_index);

  // unbind all.
  glBindVertexArray(0);
  glBindBuffer(VBO, 0);
  glUseProgram(0);


  spdlog::debug("Entering mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    // make background black
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Render triangles
    glBindVertexArray(VAO);

    glUseProgram(shdr.getShaderID());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glUseProgram(0); // unuse

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
