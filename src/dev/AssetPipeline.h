#pragma once

#include <string>
#include <vector>

namespace core_goliaf::dev {

class AssetPipeline {
public:
    void initialize();
    void enqueue(const std::string& sourcePath);
    [[nodiscard]] std::vector<std::string> build() const;

private:
    std::vector<std::string> queuedAssets_;
};

} // namespace core_goliaf::dev
