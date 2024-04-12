#include "audio.hpp"

#include <spdlog/spdlog.h>

Audio::Audio() {
  ma_result res;
  res = ma_engine_init(NULL, &engine);
  if (res != MA_SUCCESS) {
    spdlog::error("Error initializing sound engine");
  }
}

Audio::~Audio() {
  ma_engine_uninit(&engine);
}

void Audio::playSound(const char* path) {
  ma_engine_play_sound(&engine, path, NULL);
}

void setPitch(int pitch) {
}
