#include "shader.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>

std::string parseShader(std::string path) {
  spdlog::debug("reading shader {}", path);

  std::ifstream f;
  f.open(path);
  std::string line;

  std::stringstream ss;
  ss << f.rdbuf(); //read the file
  std::string read = ss.str(); //str holds the content of the file
  f.close();

  return read;
}


unsigned int compileShader(unsigned int type, const std::string src) {
  unsigned int id = glCreateShader(type);
  const char* source = src.c_str();
  glShaderSource(id, 1, &source, nullptr);
  glCompileShader(id);

  int res;
  glGetShaderiv(id, GL_COMPILE_STATUS, &res);
  if (res == GL_FALSE) {
    // thecherno includes some code that learnopengl just doesn't have...
    char infolog[512];
    glGetShaderInfoLog(id, 512, NULL, infolog);
    spdlog::error("failed to compile shader:\n {}", infolog);
  }

  return id;
}

int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  // doc these
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  // im literally zuckerberg bro
  int res;
  glGetShaderiv(program, GL_LINK_STATUS, &res);
  if (res == GL_FALSE) {
    char infolog[512];
    glGetShaderInfoLog(program, 512, NULL, infolog);
    spdlog::error("failed to link shaders:\n {}", infolog);
  }

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

