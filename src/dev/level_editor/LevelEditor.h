#pragma once

#include <cstdint>
#include <optional>
#include <unordered_map>

#include "Scene.h"

namespace core_goliaf::dev {

class LevelEditor {
public:
    struct EditableObject {
        std::uint64_t id;
        goliaf::Vec3 position;
    };

    void initialize();
    [[nodiscard]] std::uint64_t createObject(const goliaf::Vec3& position);
    bool moveObject(std::uint64_t id, const goliaf::Vec3& position);
    bool deleteObject(std::uint64_t id);
    [[nodiscard]] std::optional<EditableObject> getObject(std::uint64_t id) const;
    [[nodiscard]] std::size_t objectCount() const noexcept;

private:
    std::uint64_t nextId_{1};
    std::unordered_map<std::uint64_t, EditableObject> objects_;
};

} // namespace core_goliaf::dev
