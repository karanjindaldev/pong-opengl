#pragma once

#include <glad/gl.h>

class VertexBuffer{
private:
    unsigned int rendererID;

public:
    VertexBuffer(const void* data, unsigned int size){
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

    ~VertexBuffer(){
        glDeleteBuffers(1, &rendererID);
    }
};