cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 14)

project(gl
  VERSION "1.0.0"
  DESCRIPTION "shitty opengl"
)

file(GLOB src_files
  "src/*.cpp"
  "src/*.c"
)

add_executable(${PROJECT_NAME} ${src_files})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories("${CMAKE_SOURCE_DIR}/lib/")
include_directories("${CMAKE_SOURCE_DIR}/lib/glfw/include")

add_subdirectory("lib/spdlog/")
add_subdirectory("lib/glfw/")
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
  glfw
  spdlog::spdlog
  OpenGL::GL
)


