#include "RendererStub.h"

#include <iostream>

bool RendererStub::initialize() {
    std::cout << "[Renderer] Renderer initialized (stub/OpenGL-ready)." << std::endl;
    return true;
}

void RendererStub::renderFrame(const std::string& viewName) const {
    std::cout << "[Renderer] Rendering frame for: " << viewName << " (stub)." << std::endl;
}
