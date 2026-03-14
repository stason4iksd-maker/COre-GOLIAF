#include "dev/AssetPipeline.h"

namespace core_goliaf::dev {

void AssetPipeline::initialize() {
    queuedAssets_.clear();
}

void AssetPipeline::enqueue(const std::string& sourcePath) {
    if (!sourcePath.empty()) {
        queuedAssets_.push_back(sourcePath);
    }
}

std::vector<std::string> AssetPipeline::build() const {
    std::vector<std::string> artifacts;
    artifacts.reserve(queuedAssets_.size());
    for (const auto& asset : queuedAssets_) {
        artifacts.push_back("packed/" + asset + ".bin");
    }
    return artifacts;
}

} // namespace core_goliaf::dev
