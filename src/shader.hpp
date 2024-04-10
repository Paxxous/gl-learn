#pragma once

#include <string>

// maybe
class Shader {
  public:
    Shader(std::string vs, std::string fs);
    unsigned int getShaderID();

  private:
    unsigned int shaderProgram;

    int createShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int compileShader(unsigned int type, const std::string src);
    std::string readFile(std::string path);
};

