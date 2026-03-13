#pragma once

namespace audio {

class AudioEngine {
public:
    bool init();
    void setMasterGain(float gain);
    void update(float dt);
    void shutdown();
private:
    float phase_{0.0f};
    float gain_{0.2f};
};

}
