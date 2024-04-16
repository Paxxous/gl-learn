// i stg if my compilation is slowed down HOLY SHIT IT IS WTF
#include "img.hpp"

#include <stb_image/stb_image.h>
#include <spdlog/spdlog.h>

// load our image here
Image::Image(std::string src, bool flip) {
  if (flip) {
    stbi_set_flip_vertically_on_load(true);  
  }

  dat = stbi_load(src.c_str(), &width, &height, &nrChannels, 0);
  if (!dat) {
    spdlog::error("error loading texture {}:\n{}",
        src, stbi_failure_reason());
  }
}

Image::Image(std::string src) {
  dat = stbi_load(src.c_str(), &width, &height, &nrChannels, 0);
  if (!dat) {
    spdlog::error("error loading texture {}:\n{}",
        src, stbi_failure_reason());
  }
}

// good practice 👍
Image::~Image() {
  stbi_image_free(dat);
}

// ? should I do this or naw
int Image::getWidth() {
  return width;
}

int Image::getHeight() {
  return height;
}

unsigned char* Image::getData() {
  return dat;
}
