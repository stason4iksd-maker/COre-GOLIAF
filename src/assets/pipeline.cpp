#include "assets/pipeline.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace assets {

void Pipeline::importAssets(const std::filesystem::path& sourceDir) {
    for (const auto& e : std::filesystem::recursive_directory_iterator(sourceDir)) {
        if (e.is_regular_file()) {
            std::cout << "Import: " << e.path() << '\n';
        }
    }
}

void Pipeline::compileAndCache(const std::filesystem::path& cacheDir) {
    std::filesystem::create_directories(cacheDir);
    std::ofstream(cacheDir / "assets.pack") << "compiled_assets_v1";
}

bool Pipeline::shaderHotReload(const std::filesystem::path& shaderPath) {
    auto ts = std::filesystem::last_write_time(shaderPath);
    if (shaderTimestamp_ == std::filesystem::file_time_type{}) {
        shaderTimestamp_ = ts;
        return false;
    }
    if (ts != shaderTimestamp_) {
        shaderTimestamp_ = ts;
        std::cout << "Shader changed: " << shaderPath << '\n';
        return true;
    }
    return false;
}

}
