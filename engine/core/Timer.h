#pragma once

#include <chrono>

namespace core_goliaf::core {

class Timer {
public:
    void reset();
    double tick();

private:
    std::chrono::steady_clock::time_point last_ = std::chrono::steady_clock::now();
};

} // namespace core_goliaf::core
