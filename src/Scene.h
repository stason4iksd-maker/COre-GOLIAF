#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace goliaf {

struct Vec3 {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};

    Vec3 operator+(const Vec3& rhs) const noexcept { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
};

class Entity;

class Component {
public:
    virtual ~Component() = default;
    virtual void update(float dt) = 0;
    virtual void render() {}

    void setOwner(Entity* owner) noexcept { owner_ = owner; }

protected:
    Entity* owner_{nullptr};
};

class TransformComponent : public Component {
public:
    explicit TransformComponent(Vec3 localPosition = {});

    void setParent(TransformComponent* parent) noexcept;
    [[nodiscard]] Vec3 worldPosition() const noexcept;
    [[nodiscard]] Vec3& localPosition() noexcept;

    void update(float) override {}

private:
    Vec3 localPosition_;
    TransformComponent* parent_{nullptr};
};

class Entity {
public:
    explicit Entity(std::uint64_t id);

    std::uint64_t id() const noexcept;

    template <typename T, typename... Args>
    T& addComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        auto* raw = component.get();
        raw->setOwner(this);
        components_.push_back(std::move(component));
        return *raw;
    }

    void update(float dt);
    void render();

private:
    std::uint64_t id_;
    std::vector<std::unique_ptr<Component>> components_;
};

class Scene {
public:
    Entity& addEntity();
    void removeEntity(std::uint64_t id);
    void update(float dt);
    void render();
    std::size_t entityCount() const noexcept;

private:
    std::uint64_t nextId_{1};
    std::vector<std::unique_ptr<Entity>> entities_;
};

} // namespace goliaf
