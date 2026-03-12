#include "renderer/Mesh.h"
#include <GL/glew.h>

namespace goliaf::renderer {

bool Mesh::CreateCube() {
    // position + color
    static const float v[] = {
        // back
        -0.5f,-0.5f,-0.5f, 1,0,0,   0.5f,0.5f,-0.5f, 1,0,0,   0.5f,-0.5f,-0.5f, 1,0,0,
        -0.5f,-0.5f,-0.5f, 1,0,0,  -0.5f,0.5f,-0.5f, 1,0,0,   0.5f,0.5f,-0.5f, 1,0,0,
        // front
        -0.5f,-0.5f,0.5f, 0,1,0,   0.5f,-0.5f,0.5f, 0,1,0,   0.5f,0.5f,0.5f, 0,1,0,
        -0.5f,-0.5f,0.5f, 0,1,0,   0.5f,0.5f,0.5f, 0,1,0,   -0.5f,0.5f,0.5f, 0,1,0,
        // left
        -0.5f,0.5f,0.5f, 0,0,1,   -0.5f,0.5f,-0.5f, 0,0,1,  -0.5f,-0.5f,-0.5f, 0,0,1,
        -0.5f,0.5f,0.5f, 0,0,1,   -0.5f,-0.5f,-0.5f, 0,0,1, -0.5f,-0.5f,0.5f, 0,0,1,
        // right
        0.5f,0.5f,0.5f, 1,1,0,   0.5f,-0.5f,-0.5f, 1,1,0,   0.5f,0.5f,-0.5f, 1,1,0,
        0.5f,0.5f,0.5f, 1,1,0,   0.5f,-0.5f,0.5f, 1,1,0,   0.5f,-0.5f,-0.5f, 1,1,0,
        // bottom
        -0.5f,-0.5f,-0.5f, 1,0,1,  0.5f,-0.5f,-0.5f, 1,0,1, 0.5f,-0.5f,0.5f, 1,0,1,
        -0.5f,-0.5f,-0.5f, 1,0,1,  0.5f,-0.5f,0.5f, 1,0,1, -0.5f,-0.5f,0.5f, 1,0,1,
        // top
        -0.5f,0.5f,-0.5f, 0,1,1,  0.5f,0.5f,0.5f, 0,1,1,   0.5f,0.5f,-0.5f, 0,1,1,
        -0.5f,0.5f,-0.5f, 0,1,1, -0.5f,0.5f,0.5f, 0,1,1,   0.5f,0.5f,0.5f, 0,1,1,
    };
    vertexCount_ = 36;
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    return true;
}

void Mesh::Draw() const {
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount_);
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
}

}
