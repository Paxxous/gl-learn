#pragma once

#include <stb_image/stb_image.h>
#include <string>

class Image {
  public:
    Image(std::string src, bool flip);
    Image(std::string src); // maybe remove overload?
    ~Image();

    int getWidth();
    int getHeight();
    unsigned char* getData();


  private:
    int width, height, nrChannels;
    unsigned char* dat;
};
