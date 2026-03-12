#include "dev/debug/DebugTools.h"

#include "core/Logger.h"

namespace core_goliaf::dev {

void DebugTools::printFrameStats(double fps, double memoryMb) const {
    core::Logger::info("Debug", "FPS: " + std::to_string(static_cast<int>(fps)));
    core::Logger::info("Debug", "Memory usage: " + std::to_string(memoryMb) + " MB");
}

} // namespace core_goliaf::dev
