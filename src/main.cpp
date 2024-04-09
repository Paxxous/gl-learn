#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"

int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("project vrsn: {}", VERSION);

  spdlog::debug("reading shaders..");
  const std::string fragmentShader = parseShader("./res/shdrs/fragmentShader.glsl");
  const std::string vertexShader = parseShader("./res/shdrs/vertexShader.glsl");

  const std::string fragmentShader1 = parseShader("./res/shdrs/fragmentShader1.glsl");
  const std::string vertexShader1 = parseShader("./res/shdrs/vertexShader1.glsl");

  spdlog::debug("Setting up window..");
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("cum");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
  };

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0,
  };
  
  // idfu VAOS's yet
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  /* lets see if i understand shi */
  // Allocate VBO (space on the gput that holds our vertex data)
  unsigned int VBO; // vbo is in gpu, this is id
  glGenBuffers(1, &VBO); // generate name for buffer.
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // we now bind a type of buffer to our VBO object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy our VBO into memory

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0); // enablit
                                //
  unsigned int IBO; // vbo is in gpu, this is id
  glGenBuffers(1, &IBO); // generate name for buffer.
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); // we now bind a type of buffer to our VBO object
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), indices, GL_STATIC_DRAW); // copy our VBO into memory

  unsigned int shader = createShader(vertexShader, fragmentShader);
  unsigned int shader1 = createShader(vertexShader1, fragmentShader1);
  
  bool tog = true;
  spdlog::debug("initing mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    // THATS SO COOL IT TOGGLES SO QUICK IT TURN PURPLE LMAO
    if (tog) {
      tog = false;
      glUseProgram(shader1);
    } else {
      tog = true;
      glUseProgram(shader);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }


  glfwTerminate();
  return 0;
}
