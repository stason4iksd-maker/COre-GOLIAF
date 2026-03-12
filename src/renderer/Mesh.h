#pragma once

namespace goliaf::renderer {

class Mesh {
public:
    bool CreateCube();
    void Draw() const;
    ~Mesh();
private:
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
    int vertexCount_ = 0;
};

}
