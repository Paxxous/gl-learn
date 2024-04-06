#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "constants.hpp"
#include "window/window.hpp"


// opengl instructions here...
void gl() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

int main() {
  // CLEANNNNN
  Win win(W_WIDTH, W_HEIGHT);
  win.mainloop(gl);

  return 0;
}
