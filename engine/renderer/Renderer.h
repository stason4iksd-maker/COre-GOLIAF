#pragma once

namespace core_goliaf::renderer {

class Renderer {
public:
    bool initialize();
    void render(double deltaTime) const;
};

} // namespace core_goliaf::renderer
