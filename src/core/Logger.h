#pragma once
#include <mutex>
#include <string>

namespace goliaf::core {

class Logger {
public:
    static void Log(const std::string& tag, const std::string& message);
private:
    static std::mutex mutex_;
};

}
