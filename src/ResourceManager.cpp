#include "ResourceManager.h"

#include <stdexcept>

namespace goliaf {

Resource::Resource(std::string id, std::string path, ResourceType type)
    : id_(std::move(id)), path_(std::move(path)), type_(type) {}

const std::string& Resource::id() const noexcept { return id_; }
const std::string& Resource::path() const noexcept { return path_; }
ResourceType Resource::type() const noexcept { return type_; }

TextureResource::TextureResource(const std::string& id, const std::string& path)
    : Resource(id, path, ResourceType::Texture) {}

ModelResource::ModelResource(const std::string& id, const std::string& path)
    : Resource(id, path, ResourceType::Model) {}

SoundResource::SoundResource(const std::string& id, const std::string& path)
    : Resource(id, path, ResourceType::Sound) {}

ResourceManager& ResourceManager::instance() {
    static ResourceManager manager;
    return manager;
}

std::shared_ptr<Resource> ResourceManager::loadTexture(const std::string& path) {
    return loadImpl(path, ResourceType::Texture);
}

std::shared_ptr<Resource> ResourceManager::loadModel(const std::string& path) {
    return loadImpl(path, ResourceType::Model);
}

std::shared_ptr<Resource> ResourceManager::loadSound(const std::string& path) {
    return loadImpl(path, ResourceType::Sound);
}

std::shared_ptr<Resource> ResourceManager::getResource(const std::string& id) const {
    const auto it = resources_.find(id);
    return it == resources_.end() ? nullptr : it->second;
}

void ResourceManager::releaseResource(const std::string& id) {
    resources_.erase(id);
}

void ResourceManager::clear() {
    resources_.clear();
}

std::shared_ptr<Resource> ResourceManager::loadImpl(const std::string& path, ResourceType type) {
    if (path.empty()) {
        throw std::invalid_argument("resource path must not be empty");
    }

    const auto found = resources_.find(path);
    if (found != resources_.end()) {
        return found->second;
    }

    std::shared_ptr<Resource> created;
    switch (type) {
        case ResourceType::Texture:
            created = std::make_shared<TextureResource>(path, path);
            break;
        case ResourceType::Model:
            created = std::make_shared<ModelResource>(path, path);
            break;
        case ResourceType::Sound:
            created = std::make_shared<SoundResource>(path, path);
            break;
        default:
            created = std::make_shared<Resource>(path, path, ResourceType::Unknown);
            break;
    }

    resources_[path] = created;
    return created;
}

} // namespace goliaf
