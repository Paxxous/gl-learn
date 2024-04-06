include_directories(
  "${CMAKE_SOURCE_DIR}/lib/"
)

# l8r
add_library(WINDOW
  "window.cpp"
  "window.hpp"
)

find_package(OpenGL REQUIRED)

# deps RTAHHHH
target_link_libraries(WINDOW PRIVATE
  spdlog::spdlog
  glfw
  OpenGL::GL
)



