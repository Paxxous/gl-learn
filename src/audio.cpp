#include "audio.hpp"
#include "window.hpp"

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

  ALenum err, format;

  // read our wav file...
  SF_INFO info;
  SNDFILE* f = sf_open(path, SFM_READ, &info);
  if (!f) {
    spdlog::error("Error reading wav file: {}", sf_strerror(f));
  } else if (info.frames < 1) {
    spdlog::error("Bad sample count in {}", path);
  } else {
    spdlog::debug("Success reading {}", path);
  }

  // let's not deal ab anything above 2 channels...
  format = AL_NONE;
  switch (info.channels) {
    case 1: 
      format = AL_FORMAT_MONO16;
      break;
    case 2: 
      format = AL_FORMAT_STEREO16;
      break;
  }


  ALvoid* dat;
  dat = static_cast<short*>(malloc((size_t)(info.frames * info.channels) * sizeof(short)));

  bytes = (ALsizei)(info.frames)

  unsigned int buff;
  alGenBuffers(1, &buff);
  alBufferData(buff, format, dat, ALsizei size, info.samplerate);


  free(dat);
  sf_close(f);
}
