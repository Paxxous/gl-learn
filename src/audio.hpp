#pragma once

#include <miniaudio/miniaudio.h>

class Audio {
  public:
    Audio();
    ~Audio();

    void playSound(const char* path);

  private:
    ma_engine engine;
};

