#pragma once

#include <string>

namespace core_goliaf::dev {

class DebugTools {
public:
    void updateFrameStats(double fps, double memoryMb);
    [[nodiscard]] std::string buildOverlayText() const;

private:
    double fps_{0.0};
    double memoryMb_{0.0};
};

} // namespace core_goliaf::dev
