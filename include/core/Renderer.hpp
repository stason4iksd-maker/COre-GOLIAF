#pragma once

#include <string>

class Renderer {
public:
    void initialize();
    void renderFrame(const std::string& viewName) const;
};
