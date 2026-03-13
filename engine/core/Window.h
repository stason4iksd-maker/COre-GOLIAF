#pragma once

#include <string>

namespace core_goliaf::core {

class Window {
public:
    bool create(const std::string& title, int width, int height);
    void pollEvents();
    void close();
    bool isOpen() const;

private:
    bool open_ = false;
};

} // namespace core_goliaf::core
