#pragma once
#include <string>
#include "ecs/Registry.h"

namespace goliaf::scene {

class Scene {
public:
    explicit Scene(std::string name = "Untitled");
    const std::string& Name() const;
    goliaf::ecs::Registry& GetRegistry();
private:
    std::string name_;
    goliaf::ecs::Registry registry_;
};

}
