#include "ecs/System.h"
#include "core/Logger.h"

namespace goliaf::ecs {

void RenderSystem::Update(Registry& registry) {
    registry.ForEachTransform([](Entity, Transform&) {});
}

void ScriptSystem::Update(Registry& registry, float dt) {
    (void)registry;
    (void)dt;
}

void PhysicsSystem::Update(Registry& registry, float dt) {
    registry.ForEachTransform([dt](Entity, Transform& t) {
        t.y += 0.0f * dt;
    });
    core::Logger::Log("Physics", "initialized");
}

}
