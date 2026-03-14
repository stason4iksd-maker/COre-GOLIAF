#include "dev/level_editor/LevelEditor.h"

namespace core_goliaf::dev {

void LevelEditor::initialize() {
    objects_.clear();
    nextId_ = 1;
}

std::uint64_t LevelEditor::createObject(const goliaf::Vec3& position) {
    const auto id = nextId_++;
    objects_.insert({id, EditableObject{id, position}});
    return id;
}

bool LevelEditor::moveObject(std::uint64_t id, const goliaf::Vec3& position) {
    const auto it = objects_.find(id);
    if (it == objects_.end()) {
        return false;
    }
    it->second.position = position;
    return true;
}

bool LevelEditor::deleteObject(std::uint64_t id) {
    return objects_.erase(id) > 0;
}

std::optional<LevelEditor::EditableObject> LevelEditor::getObject(std::uint64_t id) const {
    const auto it = objects_.find(id);
    if (it == objects_.end()) {
        return std::nullopt;
    }
    return it->second;
}

std::size_t LevelEditor::objectCount() const noexcept {
    return objects_.size();
}

} // namespace core_goliaf::dev
