#include "InputManager.h"

namespace goliaf {

InputManager& InputManager::instance() {
    static InputManager input;
    return input;
}

void InputManager::processEvent(const InputEvent& event) {
    keyStates_[event.key] = event.pressed;
}

bool InputManager::isPressed(Key key) const {
    const auto it = keyStates_.find(key);
    return it != keyStates_.end() && it->second;
}

void InputManager::reset() {
    keyStates_.clear();
}

} // namespace goliaf
