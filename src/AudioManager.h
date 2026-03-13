#pragma once

#include <string>
#include <unordered_map>

namespace goliaf {

class AudioManager {
public:
    bool init();
    void shutdown();

    bool loadSound(const std::string& name, const std::string& path);
    bool playSound(const std::string& name) const;

    [[nodiscard]] bool initialized() const noexcept;

private:
    bool initialized_{false};
    std::unordered_map<std::string, std::string> sounds_;
};

} // namespace goliaf
