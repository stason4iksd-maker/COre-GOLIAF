#include "dev/debug/DebugTools.h"

#include <sstream>

namespace core_goliaf::dev {

void DebugTools::updateFrameStats(double fps, double memoryMb) {
    fps_ = fps;
    memoryMb_ = memoryMb;
}

std::string DebugTools::buildOverlayText() const {
    std::ostringstream oss;
    oss << "[DebugOverlay] FPS=" << static_cast<int>(fps_) << " MEM=" << memoryMb_ << "MB";
    return oss.str();
}

} // namespace core_goliaf::dev
