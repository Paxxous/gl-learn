#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "window.hpp"

void err_callback(int err, const char *description) {
  spdlog::error("{} err: {}", err, description);
}

void framebuff_resize_callback(GLFWwindow *window, int w, int h) {
  glViewport(0, 0, w, h);
}

Win::Win(int w_w, int w_h)
  : window_width(w_w), window_height(w_h)
{
  glfwInit();
  

  glfwSetErrorCallback(err_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  win = glfwCreateWindow(window_width, window_height, ".", NULL, NULL);
  if (win == NULL) {
    glfwTerminate();
  }

  glfwMakeContextCurrent(win);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    spdlog::error("failed to init glad");
  }
}

void Win::set_title(const char* t) {
  glfwSetWindowTitle(win, t);
}

void Win::mainloop(void(*loop)()) {
  glViewport(0, 0, window_width, window_height);
  glfwSetFramebufferSizeCallback(win, framebuff_resize_callback);

  while (!glfwWindowShouldClose(win)) {
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, true);

    loop(); // all the opengl shi happens here

    glfwSwapBuffers(win);
    glfwPollEvents();
  }

  glfwTerminate();
}
