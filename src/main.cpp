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

  spdlog::debug("Setting up window..");
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("triangle fucking you");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,

     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
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
                                                                             //
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // tell gl how to use our data
  glEnableVertexAttribArray(0); // enablit

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeof(float) * 9));
  glEnableVertexAttribArray(1); // enable

  unsigned int shader = createShader(vertexShader, fragmentShader);
  
  spdlog::debug("initing mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    float time = glfwGetTime();
    float clr = (sin(time * 50)) + 3;
    // spdlog::debug("{}", clr);

    int vertexColorLocation = glGetUniformLocation(shader, "posQ");
    glUniform1f(vertexColorLocation, clr);
    glUseProgram(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }


  glfwTerminate();
  return 0;
}
