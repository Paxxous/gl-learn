#include "audio.hpp"

#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>

#include <spdlog/spdlog.h>

ALvoid* readWAV(const char* path, ALenum &format, ALsizei &size, ALsizei &samplerate) {
  SF_INFO info;
  SNDFILE* f = sf_open(path, SFM_READ, &info);
  if (!f) {
    spdlog::error("Error reading wav file: {}", sf_strerror(f));
  } else if (info.frames < 1) {
    spdlog::error("Bad sample count in {}", path);
  } else {
    spdlog::debug("Success reading {}", path);
  }

  // now we have to fucking decode everything :sob:


  sf_close(f);
  return (void*)0; // for now
}

void playSound(const char* path) {
  ALCdevice* device = alcOpenDevice(NULL);
  ALCcontext* context;
  if (device) {
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
  } else {
    spdlog::error("Error loading audio file");
  }

  ALenum format;
  ALsizei size;
  ALsizei freq;
  ALboolean loop;
  ALvoid *dat = readWAV(path, format, size, freq);
  // spdlog::debug("{}, {}, {}", format, size, freq);

  unsigned int buff;
  alGenBuffers(1, &buff);
  // alBufferData(ALuint buffer, ALenum format, const ALvoid *data, ALsizei size, ALsizei samplerate)


  alGetError();


}

