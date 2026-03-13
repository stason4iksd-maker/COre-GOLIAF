#pragma once

#include <unordered_map>

namespace goliaf {

enum class Key {
    W,
    A,
    S,
    D,
    Escape,
    MouseLeft
};

struct InputEvent {
    Key key;
    bool pressed;
};

class InputManager {
public:
    static InputManager& instance();

    void processEvent(const InputEvent& event);
    bool isPressed(Key key) const;
    void reset();

private:
    std::unordered_map<Key, bool> keyStates_;
};

} // namespace goliaf
