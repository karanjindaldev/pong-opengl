#pragma once

#include <glad/gl.h>

class IndexBuffer{
private:
    unsigned int rendererID;

public:
    unsigned int count = 0;

    IndexBuffer(const void* data, unsigned int size)
    : count(size/sizeof(unsigned int)){
        glGenBuffers(1, &(this->rendererID));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
    }

    void Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ~IndexBuffer(){
        glDeleteBuffers(1, &rendererID);
    }
};