#include "shader.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <spdlog/spdlog.h>
#include <glad/glad.h>

Shader::Shader(std::string vs, std::string fs) {
  spdlog::debug("reading VertexShader: {}", vs);
  std::string vssrc = readFile(vs);

  spdlog::debug("reading FragmentShader: {}", fs);
  std::string fssrc = readFile(fs);

  shaderProgram = createShader(vssrc, fssrc);
}

std::string Shader::readFile(std::string path) {
  std::string read;
  std::ifstream f;
  f.open(path);
  std::string line;

  std::stringstream ss;
  ss << f.rdbuf(); //read the file
  read = ss.str(); //str holds the content of the file
  f.close();

  return read;
}


int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
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

unsigned int Shader::compileShader(unsigned int type, const std::string src) {
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
    spdlog::error("failed to compile shader {}:\n {}", src, infolog);
  }

  return id;
}

unsigned int Shader::getShaderID() {
  return shaderProgram;
}
