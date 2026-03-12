#include "audio/AudioEngine.h"

#include "core/Logger.h"

namespace core_goliaf::audio {

bool AudioEngine::initialize() {
    core::Logger::info("Audio", "Initialized");
    return true;
}

void AudioEngine::update() const {
    core::Logger::info("Audio", "Update tick");
}

} // namespace core_goliaf::audio
