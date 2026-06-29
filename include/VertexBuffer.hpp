#pragma once

#include <glad/gl.h>

class VertexBuffer{
private:
    unsigned int rendererID;
    unsigned int vertexCount;

public:
    VertexBuffer(const void* data, unsigned int size)
    : vertexCount(size/sizeof(float)) {
        glGenBuffers(1, &(this->rendererID));
        glBindBuffer(GL_ARRAY_BUFFER, this->rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID);
    }

    void Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    unsigned int GetVertexCount() const {
        return this->vertexCount;
    }

    ~VertexBuffer(){
        glDeleteBuffers(1, &rendererID);
    }
};