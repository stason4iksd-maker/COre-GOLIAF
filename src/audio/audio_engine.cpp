#include "audio/audio_engine.hpp"
#include <cmath>

namespace audio {

bool AudioEngine::init() {
    phase_ = 0.0f;
    return true;
}

void AudioEngine::setMasterGain(float gain) { gain_ = gain; }

void AudioEngine::update(float dt) {
    // Minimal real-time tone generator state update (engine-side, backend-agnostic).
    phase_ += dt * 440.0f * 6.2831853f;
    if (phase_ > 6.2831853f) phase_ -= 6.2831853f;
    [[maybe_unused]] float sample = std::sin(phase_) * gain_;
}

void AudioEngine::shutdown() {}

}
