#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"
#include "img.hpp"

// https://docs.gl/
int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("project vrsn: {}", VERSION);

  spdlog::debug("Setting up window..");
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("window");

  // load our resources
  Shader shdr = Shader(
    "./res/shdrs/vertexShader.glsl",
    "./res/shdrs/fragmentShader.glsl"
  );

  // define our vertices (no it is not a square >:( )
  float vertices[] = {
    // vertices
    0.0f, 0.75f, 0.0f,
    -0.75f, -0.75f, 0.0f,
    0.75f, -0.75f, 0.0f,

    // colors
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    
    // image textures
    1.5f, 3.0f,
    3.0f, 0.0f,
    0.0, 0.0f,
  };

  // create VAO
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // allocate mem and upload vertices to gpu
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // tell gpu how to parse pos vertices
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
  glEnableVertexAttribArray(0);

  // now tell it how to parse color verts
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)(sizeof(float) * 9));
  glEnableVertexAttribArray(1);

  // now tell it how to parse the texture coords
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(float) * 18));
  glEnableVertexAttribArray(2);

  unsigned int wood_texture;
  glGenTextures(1, &wood_texture);
  glBindTexture(GL_TEXTURE_2D, wood_texture);

  // configure image wrapping for both S and T axis (s+t correspond to x+y)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  // set up how mipmaps are also filtered (im reusing code i thnk lmao ill deal withit later)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  Image wood = Image("./res/img/wood.jpg", true);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wood.getWidth(), wood.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, wood.getData());
  glGenerateMipmap(GL_TEXTURE_2D);

  unsigned int well_texture;
  glGenTextures(1, &well_texture);
  glBindTexture(GL_TEXTURE_2D, well_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  Image me = Image("./res/img/welly.jpg", true);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, me.getWidth(), me.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, me.getData());
  glGenerateMipmap(GL_TEXTURE_2D);

  glUseProgram(shdr.getShaderID());
  glUniform1i(glGetUniformLocation(shdr.getShaderID(), "tex1"), 0);
  glUniform1i(glGetUniformLocation(shdr.getShaderID(), "tex2"), 1);

  // unbind all.
  // glBindVertexArray(0);
  // glBindBuffer(VBO, 0);
  // glUseProgram(0);

  spdlog::debug("Entering mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    // make background black
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wood_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, well_texture);

    // Render triangles
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glUseProgram(0); // unuse

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
