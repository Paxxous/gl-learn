#pragma once

#include <string>

// not a class yet.
unsigned int compileShader(unsigned int type, const std::string src);
int createShader(const std::string& vertexShader, const std::string& fragmentShader);
