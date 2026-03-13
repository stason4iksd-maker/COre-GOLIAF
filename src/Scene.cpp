#include "Scene.h"

#include <algorithm>
#include <utility>

namespace goliaf {

TransformComponent::TransformComponent(Vec3 localPosition) : localPosition_(localPosition) {}

void TransformComponent::setParent(TransformComponent* parent) noexcept { parent_ = parent; }

Vec3 TransformComponent::worldPosition() const noexcept {
    return parent_ ? parent_->worldPosition() + localPosition_ : localPosition_;
}

Vec3& TransformComponent::localPosition() noexcept { return localPosition_; }

Entity::Entity(std::uint64_t id) : id_(id) {}

std::uint64_t Entity::id() const noexcept { return id_; }

void Entity::update(float dt) {
    for (const auto& component : components_) {
        component->update(dt);
    }
}

void Entity::render() {
    for (const auto& component : components_) {
        component->render();
    }
}

Entity& Scene::addEntity() {
    auto entity = std::make_unique<Entity>(nextId_++);
    auto* raw = entity.get();
    entities_.push_back(std::move(entity));
    return *raw;
}

void Scene::removeEntity(std::uint64_t id) {
    entities_.erase(
        std::remove_if(entities_.begin(), entities_.end(), [id](const auto& entity) { return entity->id() == id; }),
        entities_.end());
}

void Scene::update(float dt) {
    for (const auto& entity : entities_) {
        entity->update(dt);
    }
}

void Scene::render() {
    for (const auto& entity : entities_) {
        entity->render();
    }
}

std::size_t Scene::entityCount() const noexcept { return entities_.size(); }

} // namespace goliaf
