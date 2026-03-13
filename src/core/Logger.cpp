#include "core/Logger.h"
#include <iostream>

namespace goliaf::core {
std::mutex Logger::mutex_;
void Logger::Log(const std::string& tag, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << '[' << tag << "] " << message << std::endl;
}
}
