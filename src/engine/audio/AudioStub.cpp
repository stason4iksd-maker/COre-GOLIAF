#include "AudioStub.h"

#include <iostream>

bool AudioStub::initialize() {
    std::cout << "[Audio] Audio initialized (stub)." << std::endl;
    return true;
}

void AudioStub::update() const {
    std::cout << "[Audio] Update tick (stub)." << std::endl;
}
