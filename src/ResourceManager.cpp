#include "ResourceManager.h"

#include <filesystem>
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

std::shared_ptr<Resource> ResourceManager::LoadTexture(const std::string& path) {
    return loadTexture(path);
}

std::shared_ptr<Resource> ResourceManager::LoadModel(const std::string& path) {
    return loadModel(path);
}

std::shared_ptr<Resource> ResourceManager::LoadSound(const std::string& path) {
    return loadSound(path);
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
    const auto normalizedId = normalizeId(id);
    const std::lock_guard<std::mutex> lock(mutex_);
    const auto it = resources_.find(normalizedId);
    return it == resources_.end() ? nullptr : it->second;
}

std::shared_ptr<Resource> ResourceManager::GetResource(const std::string& id) const {
    return getResource(id);
}

void ResourceManager::releaseResource(const std::string& id) {
    const auto normalizedId = normalizeId(id);
    const std::lock_guard<std::mutex> lock(mutex_);
    resources_.erase(normalizedId);
}

void ResourceManager::ReleaseResource(const std::string& id) {
    releaseResource(id);
}

void ResourceManager::clear() {
    const std::lock_guard<std::mutex> lock(mutex_);
    resources_.clear();
}

std::shared_ptr<Resource> ResourceManager::loadImpl(const std::string& path, ResourceType type) {
    if (path.empty()) {
        throw std::invalid_argument("resource path must not be empty");
    }

    const auto id = normalizeId(path);
    const std::lock_guard<std::mutex> lock(mutex_);
    const auto found = resources_.find(id);
    if (found != resources_.end()) {
        return found->second;
    }

    std::shared_ptr<Resource> created;
    switch (type) {
        case ResourceType::Texture:
            created = std::make_shared<TextureResource>(id, path);
            break;
        case ResourceType::Model:
            created = std::make_shared<ModelResource>(id, path);
            break;
        case ResourceType::Sound:
            created = std::make_shared<SoundResource>(id, path);
            break;
        default:
            created = std::make_shared<Resource>(id, path, ResourceType::Unknown);
            break;
    }

    resources_[id] = created;
    return created;
}

std::string ResourceManager::normalizeId(const std::string& path) {
    const std::filesystem::path fsPath(path);
    return fsPath.lexically_normal().generic_string();
}

} // namespace goliaf
