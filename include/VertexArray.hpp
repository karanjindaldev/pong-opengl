#pragma once

#include <glad/gl.h>

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray{
private:
    unsigned int rendererID;

public:
    unsigned int vertexCount;

    VertexArray(){
        glCreateVertexArrays(1, &rendererID);
    }

    void AddBufferAndLayout(const VertexBuffer& vbo, const VertexBufferLayout& layout){
        this->vertexCount = vbo.GetVertexCount();
        int offset = 0;
        vbo.Bind();
        this->Bind();
        for(int i=0; i<layout.elements.size(); i++){
            glVertexAttribPointer(i, layout.elements[i].count, layout.elements[i].type, GL_FALSE, layout.stride, (const void*)offset);
            glEnableVertexAttribArray(i);
            offset+=layout.elements[i].count*VertexLayoutElement::GetElementTypeSize(layout.elements[i].type);
        }
        this->Unbind();
    }

    void Bind() const {
        glBindVertexArray(rendererID);
    }

    void Unbind() const {
        glBindVertexArray(rendererID);
    }

    ~VertexArray(){
        glDeleteVertexArrays(1, &rendererID);
    }
};