#pragma once

#include <stb_image/stb_image.h>
#include <string>

class Image {
  public:
    Image(std::string src);
    ~Image();

    int getWidth();
    int getHeight();
    // unsigned char* data();

    unsigned char* dat;

  private:
    int width, height, nrChannels;
};
