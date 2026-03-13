#pragma once

#include <string>

namespace core_goliaf::core {

class Logger {
public:
    static void info(const std::string& tag, const std::string& message);
};

} // namespace core_goliaf::core
