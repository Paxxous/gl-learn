#pragma once

#include <miniaudio/miniaudio.h>

class Audio {
  public:
    Audio();
   ~Audio();

    void playSound(const char* path);
    void setPitch(int pitch);

  private:
    ma_engine engine;
};

