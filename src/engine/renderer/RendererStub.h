#pragma once

#include <string>

class RendererStub {
public:
    bool initialize();
    void renderFrame(const std::string& viewName) const;
};
