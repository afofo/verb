#include "lv2/lv2plug.in/ns/lv2core/lv2.h"
#include <string>

static const std::string AVERB_URI = "https://github.com/afofo/verb#averb";

typedef enum {
  AVERB_SIZE  = 0,
  AVERB_DECAY = 1,
  AVERB_TONE  = 2,
  AVERB_MIX   = 3,
  AVERB_IN    = 4,
  AVERB_OUT   = 5,
  AVERB_IN_L  = 6,
  AVERB_IN_R  = 7,
  AVERB_OUT_L = 8,
  AVERB_OUT_R = 9
} PortIndex;

struct Averb {
  const float* size;
  const float* decay;
  const float* tone;
  const float* mix;
  const float* in;
  const float* out;

  const float* in_left;
  const float* in_right;
  float*       out_left;
  float*       out_right;
};


static LV2_Handle instantiate(const LV2_Descriptor* descriptor, double rate, const char* bundle_path,
                              const LV2_Feature* const* features) {
  Averb* verb = new Averb;
  return (LV2_Handle)verb;
};

static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
  Averb* verb = static_cast<Averb*>(instance);
  switch ((PortIndex)port) {
  case AVERB_SIZE:
    verb->size = static_cast<const float*>(data);
    break;
  case AVERB_DECAY:
    verb->decay = static_cast<const float*>(data);
    break;
  case AVERB_TONE:
    verb->tone = static_cast<const float*>(data);
    break;
  case AVERB_MIX:
    verb->mix = static_cast<const float*>(data);
    break;
  case AVERB_IN:
    verb->in = static_cast<const float*>(data);
    break;
  case AVERB_OUT:
    verb->out = static_cast<const float*>(data);
    break;
  case AVERB_IN_L:
    verb->in_left = static_cast<const float*>(data);
    break;
  case AVERB_IN_R:
    verb->in_right = static_cast<const float*>(data);
    break;
  case AVERB_OUT_L:
    verb->out_left = static_cast<float*>(data);
    break;
  case AVERB_OUT_R:
    verb->out_right = static_cast<float*>(data);
    break;
  }
}

static void activate(LV2_Handle instance) {
}

static void run(LV2_Handle instance, uint32_t n_samples) {
  // TODO:
}

static void deactivate(LV2_Handle instance) {
}

static void cleanup(LV2_Handle instance) {
  Averb* verb = static_cast<Averb*>(instance);
  delete verb;
}

static const void* extension_data(const char* uri) {
  return nullptr;
}

static const LV2_Descriptor descriptor = {
  AVERB_URI.c_str(),
  instantiate,
  connect_port,
  activate,
  run,
  deactivate,
  cleanup,
  extension_data
};

#ifdef __cplusplus
extern "C"
{
#endif

LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index) {
  switch (index) {
  case 0:
    return &descriptor;
  }
  return nullptr;
}

#ifdef __cplusplus
} // extern "C"
#endif

