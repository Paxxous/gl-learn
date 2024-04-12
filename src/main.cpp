// FUCK YOU MINIAUDIO WHY IS MY COMPILER SO FUKCING SLOW AGGGG
#define GLFW_INCLUDE_NONE
#define MINIAUDIO_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
// #include <iostream>
#include <fstream>

#include "audio.hpp"
#include "constants.hpp"
#include "shader.hpp"
#include "window.hpp"

// lmao
void grabConfig(int &s, std::string &p) {
  std::fstream f("config.json");
  nlohmann::json dat = nlohmann::json::parse(f);

  // holy modern c++ (i gotta learn that)
  int fuckspeed = dat["speed"].template get<int>();
  std::string soundpath = dat["sound"].template get<std::string>();

  spdlog::debug("fucking speed: {}", std::to_string(fuckspeed));
  spdlog::debug("fuck sound: {}", soundpath);

  p = soundpath;
  s = fuckspeed;
}

int main() {
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("project vrsn: {}", VERSION);

  spdlog::debug("Setting up window..");
  Win win(W_WIDTH, W_HEIGHT);
  GLFWwindow *handle = win.getWinHandle();
  win.setTitle("window fucks you");

  Audio aud = Audio();

  int speed;
  std::string soundpath;
  grabConfig(speed, soundpath);

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
  unsigned int VBO;      // vbo is in gpu, this is id
  glGenBuffers(1, &VBO); // generate name for buffer.
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // we now bind a type of buffer to our VBO object
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // copy our VBO into memory

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // tell gl how to use our data
  glEnableVertexAttribArray(0); // enablit

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)(sizeof(float) * 9));
  glEnableVertexAttribArray(1); // enable

  Shader shader = Shader(
    "./res/shdrs/vertexShader.glsl",
    "./res/shdrs/fragmentShader.glsl"
  );

  float clrPrev = 0;
  bool togg = false;
  unsigned int fucked = 0;
  std::string title;

  spdlog::debug("Entering mainloop");
  while (!glfwWindowShouldClose(handle)) {
    if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(handle, true);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    float time = glfwGetTime();
    float clr = (sin(time * speed)) + 1.25f;

    if (clrPrev < clr && togg == true) {
      title = std::string("triangle fucks you ") += std::to_string(fucked) += std::string(" times");
      win.setTitle(title.c_str());
      aud.playSound(soundpath.c_str());

      fucked++;
      togg = false;
    } else if (clrPrev > clr && togg == false) {
      togg = true;
    }

    clrPrev = clr;

    int vertexColorLocation = glGetUniformLocation(shader.getShaderID(), "posQ");
    glUniform1f(vertexColorLocation, clr);
    glUseProgram(shader.getShaderID());
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(handle);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
