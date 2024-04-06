#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>


class Win {
  private:
    int window_width;
    int window_height;

    GLFWwindow *win;

  public:
    Win(int w_w, int w_h);
    
    void set_title(const char* t);
    void mainloop(void(*loop)());
};

void err_callback(int err, const char *description);
void framebuff_resize_callback(GLFWwindow *window, int w, int h);
