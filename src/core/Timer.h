#pragma once
#include <chrono>

namespace goliaf::core {
class Timer {
public:
    Timer();
    void Reset();
    float Tick();
private:
    std::chrono::steady_clock::time_point last_;
};
}
