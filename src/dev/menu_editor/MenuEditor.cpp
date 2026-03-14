#include "dev/menu_editor/MenuEditor.h"

#include <algorithm>

namespace core_goliaf::dev {

void MenuEditor::initialize() {
    buttons_.clear();
}

bool MenuEditor::addButton(const std::string& id, const std::string& title, int x, int y) {
    if (id.empty() || buttons_.count(id) > 0U) {
        return false;
    }
    buttons_.insert({id, MenuButton{id, title, x, y}});
    return true;
}

bool MenuEditor::moveButton(const std::string& id, int x, int y) {
    const auto it = buttons_.find(id);
    if (it == buttons_.end()) {
        return false;
    }
    it->second.x = x;
    it->second.y = y;
    return true;
}

bool MenuEditor::removeButton(const std::string& id) {
    return buttons_.erase(id) > 0U;
}

std::vector<MenuEditor::MenuButton> MenuEditor::listButtons() const {
    std::vector<MenuButton> out;
    out.reserve(buttons_.size());
    for (const auto& [_, button] : buttons_) {
        out.push_back(button);
    }
    std::sort(out.begin(), out.end(), [](const MenuButton& lhs, const MenuButton& rhs) {
        return lhs.id < rhs.id;
    });
    return out;
}

} // namespace core_goliaf::dev
