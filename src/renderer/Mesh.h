#pragma once

namespace goliaf::renderer {

class Mesh {
public:
    bool CreateTriangle();
    void Draw() const;
    ~Mesh();
private:
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
};

}
