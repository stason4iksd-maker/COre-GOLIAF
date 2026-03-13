#pragma once
#include <filesystem>

namespace assets {

class Pipeline {
public:
    void importAssets(const std::filesystem::path& sourceDir);
    void compileAndCache(const std::filesystem::path& cacheDir);
    bool shaderHotReload(const std::filesystem::path& shaderPath);
private:
    std::filesystem::file_time_type shaderTimestamp_{};
};

}
