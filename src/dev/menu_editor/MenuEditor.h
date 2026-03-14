#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace core_goliaf::dev {

class MenuEditor {
public:
    struct MenuButton {
        std::string id;
        std::string title;
        int x{0};
        int y{0};
    };

    void initialize();
    bool addButton(const std::string& id, const std::string& title, int x, int y);
    bool moveButton(const std::string& id, int x, int y);
    bool removeButton(const std::string& id);
    [[nodiscard]] std::vector<MenuButton> listButtons() const;

private:
    std::unordered_map<std::string, MenuButton> buttons_;
};

} // namespace core_goliaf::dev
