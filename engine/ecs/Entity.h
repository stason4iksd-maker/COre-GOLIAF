#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "ecs/Component.h"

namespace core_goliaf::ecs {

class Entity {
public:
    explicit Entity(int id) : id_(id) {}

    template <typename T, typename... Args>
    T& addComponent(Args&&... args) {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        components_[std::type_index(typeid(T))] = component;
        return *component;
    }

    template <typename T>
    bool hasComponent() const {
        return components_.find(std::type_index(typeid(T))) != components_.end();
    }

    int id() const { return id_; }

private:
    int id_;
    std::unordered_map<std::type_index, std::shared_ptr<IComponent>> components_;
};

} // namespace core_goliaf::ecs
