#pragma once
#include <string>

namespace goliaf::ecs {

struct Transform {
    float x{0};
    float y{0};
    float z{0};
};

struct MeshRenderer {
    bool visible{true};
};

struct Camera {
    float speed{2.0f};
};

struct Script {
    std::string path;
};

}
