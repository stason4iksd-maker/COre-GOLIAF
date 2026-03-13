#include "core/Timer.h"

namespace core_goliaf::core {

void Timer::reset() {
    last_ = std::chrono::steady_clock::now();
}

double Timer::tick() {
    const auto now = std::chrono::steady_clock::now();
    const std::chrono::duration<double> delta = now - last_;
    last_ = now;
    return delta.count();
}

} // namespace core_goliaf::core
