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
  win.setTitle("cum");

  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };
  
  // idfu VAOS's yet
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  /* lets see if i understand shi */
  // Allocate VBO (space on the gput that holds our vertex data)
  unsigned int VBO; // (remember that the VBO is something that is allocated in GPU storage,
                    // this is just an id that we use in order to access this data from gpu)
  glGenBuffers(1, &VBO); // generate name for buffer.
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // we now bind a type of buffer to our VBO object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy our VBO into memory
                                                                            // chat am i finally understanding

  unsigned int shader = createShader(vertexShader, fragmentShader);

  // we must manually tell opengl how to take in the vertices...
  glVertexAttribPointer(
    0, // "which vertext attrib to configure" fuck if i know
    3, // the amount of points pretty much (vec3, three points)
    GL_FLOAT, // type of data, it is obviously a float...
    GL_FALSE, // if we basically want to cut our numbers in betwen 1 and 0
              // (exmaple being colors, which are usually 0 to 255)
    3 * sizeof(float), // Size of each point, and every point is thre floats..
    (void*)0 // idfk offset..?
  );

  glEnableVertexAttribArray(0); // enablit
  
  spdlog::debug("initing mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }


  glfwTerminate();
  return 0;
}
