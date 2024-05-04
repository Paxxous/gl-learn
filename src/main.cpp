#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"

// rewrite from scratch
int main() {
  spdlog::set_level(spdlog::level::debug);

  Win window(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = window.getWinHandle();
  window.setTitle("window");

  float verts[] = {
    1.0, 0.5, 0.0,
    -1.0, -1.0, 0.0,
    -1.0, 1.0, 0.0
  };

  // gl pipeline
  unsigned int VAO;
  glGenBuffers(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, verts, GL_STATIC_DRAW);

  Shader shdr(
    "./res/shdrs/vertexShader.glsl",
    "./res/shdrs/fragmentShader.glsl"
  );

  // read the verts
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);

  bool epilespyToggle = true;
  while (!glfwWindowShouldClose(handle)) {
    glfwPollEvents();

    // rendering..

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
}
