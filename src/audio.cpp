#include "audio.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <spdlog/spdlog.h>

void playSound(const char* path) {
  ALCdevice* device = alcOpenDevice(NULL);
  ALCcontext* context;
  if (device) {
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
  } else {
    spdlog::error("Error loading audio file");
  }

  alGetError();

  SF_INFO info;
  SNDFILE* f = sf_open(path, SFM_READ, &info);

  unsigned int buf;
  alGenBuffers(1, &buf);
  alBufferData(buf, info.format, f, sizeof(f), info.samplerate);

  sf_close(f);
}
