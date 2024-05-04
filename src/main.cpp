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
#include "img.hpp"

int main() {
  spdlog::set_level(spdlog::level::debug);

  Win window(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = window.getWinHandle();
  window.setTitle("window");

  float verts[] = {
    // positions
    0.75f, 0.75f, 0.0f, // 0
    0.75f, -0.75f, 0.0f, // 1
    -0.75f, -0.75f, 0.0f, // 2
    -0.75f, 0.75f, 0.0f, // 3

    // colors
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f,

    // texture pos
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f,
  };

  unsigned int indices[] {
    0, 1, 3,
    1, 2, 3
  };

  Shader shdr(
    "./res/shdrs/vertexShader.glsl",
    "./res/shdrs/fragmentShader.glsl"
  );

  Image welly("./res/img/welly.jpg", true);
  Image horn("./res/img/horn.jpg", true);

  // gl pipeline
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 12));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(float) * 24));
  glEnableVertexAttribArray(2);

  unsigned int wellyimg;
  glGenTextures(1, &wellyimg);
  glBindTexture(GL_TEXTURE_2D, wellyimg);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, welly.getWidth(), welly.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, welly.getData());
  glGenerateMipmap(GL_TEXTURE_2D);

  unsigned int hornimg;
  glGenTextures(1, &hornimg);
  glBindTexture(GL_TEXTURE_2D, hornimg);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, horn.getWidth(), horn.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, horn.getData());
  glGenerateMipmap(GL_TEXTURE_2D);

  bool epilespyToggle = true;
  while (!glfwWindowShouldClose(handle)) {
    glfwPollEvents();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shdr.getShaderID());

    glUniform1i(glGetUniformLocation(shdr.getShaderID(), "tex1"), 0);
    glUniform1i(glGetUniformLocation(shdr.getShaderID(), "tex2"), 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wellyimg);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, hornimg);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
}
