#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace goliaf {

enum class ResourceType {
    Texture,
    Model,
    Sound,
    Shader,
    Unknown
};

class Resource {
public:
    Resource(std::string id, std::string path, ResourceType type);
    virtual ~Resource() = default;

    const std::string& id() const noexcept;
    const std::string& path() const noexcept;
    ResourceType type() const noexcept;

private:
    std::string id_;
    std::string path_;
    ResourceType type_;
};

class TextureResource final : public Resource {
public:
    TextureResource(const std::string& id, const std::string& path);
};

class ModelResource final : public Resource {
public:
    ModelResource(const std::string& id, const std::string& path);
};

class SoundResource final : public Resource {
public:
    SoundResource(const std::string& id, const std::string& path);
};

class ResourceManager {
public:
    static ResourceManager& instance();

    std::shared_ptr<Resource> LoadTexture(const std::string& path);
    std::shared_ptr<Resource> LoadModel(const std::string& path);
    std::shared_ptr<Resource> LoadSound(const std::string& path);

    std::shared_ptr<Resource> loadTexture(const std::string& path);
    std::shared_ptr<Resource> loadModel(const std::string& path);
    std::shared_ptr<Resource> loadSound(const std::string& path);

    std::shared_ptr<Resource> getResource(const std::string& id) const;
    std::shared_ptr<Resource> GetResource(const std::string& id) const;
    void releaseResource(const std::string& id);
    void ReleaseResource(const std::string& id);
    void clear();

private:
    ResourceManager() = default;

    std::shared_ptr<Resource> loadImpl(const std::string& path, ResourceType type);
    static std::string normalizeId(const std::string& path);

    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::shared_ptr<Resource>> resources_;
};

} // namespace goliaf
