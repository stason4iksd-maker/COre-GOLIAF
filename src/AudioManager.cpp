#include "AudioManager.h"

#include <fstream>

namespace goliaf {

bool AudioManager::init() {
    initialized_ = true;
    return true;
}

void AudioManager::shutdown() {
    sounds_.clear();
    initialized_ = false;
}

bool AudioManager::loadSound(const std::string& name, const std::string& path) {
    if (!initialized_) {
        return false;
    }
    std::ifstream source(path);
    if (!source.good()) {
        return false;
    }
    sounds_[name] = path;
    return true;
}

bool AudioManager::playSound(const std::string& name) const {
    return initialized_ && sounds_.count(name) > 0;
}

bool AudioManager::initialized() const noexcept {
    return initialized_;
}

} // namespace goliaf
