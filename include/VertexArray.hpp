#pragma once

#include <glad/gl.h>

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

#include <iostream>

class VertexArray{
private:
    unsigned int renderedID;

public:
    VertexArray(){
        glCreateVertexArrays(1, &renderedID);
    }

    void AddBufferAndLayout(const VertexBuffer& vbo, const VertexBufferLayout& layout){
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
        glBindVertexArray(renderedID);
    }

    void Unbind() const {
        glBindVertexArray(renderedID);
    }

    ~VertexArray(){
        glDeleteVertexArrays(1, &renderedID);
    }
};