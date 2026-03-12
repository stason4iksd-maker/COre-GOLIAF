#include "core/Timer.h"
namespace goliaf::core {
Timer::Timer() { Reset(); }
void Timer::Reset() { last_ = std::chrono::steady_clock::now(); }
float Timer::Tick() {
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> dt = now - last_;
    last_ = now;
    return dt.count();
}
}
