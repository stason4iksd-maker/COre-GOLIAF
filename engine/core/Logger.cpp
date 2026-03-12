#include "core/Logger.h"

#include <iostream>

namespace core_goliaf::core {

void Logger::info(const std::string& tag, const std::string& message) {
    std::cout << '[' << tag << "] " << message << std::endl;
}

} // namespace core_goliaf::core
