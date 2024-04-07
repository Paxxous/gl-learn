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
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); FUCK YOU MACKINTOSH I EIL:
  //
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  win = glfwCreateWindow(window_width, window_height, ".", NULL, NULL);
  if (win == NULL) { // maybe log it?
    glfwTerminate();
  }

  glfwMakeContextCurrent(win);

  glfwSetFramebufferSizeCallback(win, framebuff_resize_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    spdlog::error("failed to init glad");
  }
}

void Win::setTitle(const char* t) {
  glfwSetWindowTitle(win, t);
}

GLFWwindow* Win::getWinHandle() {
  return win;
}
