#pragma once

#include <string>

std::string parseShader(std::string path);
unsigned int compileShader(unsigned int type, const std::string src);
int createShader(const std::string& vertexShader, const std::string& fragmentShader);
