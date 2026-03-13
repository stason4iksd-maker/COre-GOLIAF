#pragma once

#include <string>

class Renderer;
class PhysicsSystem;
class AudioSystem;
class EcsWorld;

class Engine {
public:
    void initialize();
    void update(double deltaTime);
    void shutdown();

private:
    bool initialized_{false};
};
