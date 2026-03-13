#include "core/Renderer.hpp"

#include <iostream>

void Renderer::initialize() {
    std::cout << "[Render] Renderer initialized" << std::endl;
}

void Renderer::renderFrame(const std::string& viewName) const {
    std::cout << "[Render] Rendering view: " << viewName << std::endl;
}
