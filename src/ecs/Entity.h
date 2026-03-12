#pragma once
#include <cstdint>
#include <string>

namespace goliaf::ecs {
using Entity = std::uint32_t;
struct EntityInfo {
    Entity id{};
    std::string name;
};
}
