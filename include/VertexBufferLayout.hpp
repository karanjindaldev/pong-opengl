#pragma once

#include <glad/gl.h>
#include <vector>

template<typename T>
bool always_false = false;

struct VertexLayoutElement {
    unsigned int count;
    unsigned int type;

    VertexLayoutElement(unsigned int count, unsigned int type)
    : count(count), type(type) {}

    static unsigned int GetElementTypeSize(const unsigned int type) {
        switch(type){
            case GL_FLOAT:
                return sizeof(float);
                break;
            case GL_UNSIGNED_INT:
                return sizeof(unsigned int);
                break;
            case GL_INT:
                return sizeof(int);
                break;
            case GL_UNSIGNED_BYTE:
                return sizeof(char);
                break;
        }
        return 0;
    }
};

class VertexBufferLayout{
public:
    std::vector<VertexLayoutElement> elements;
    unsigned int stride = 0;

    template<typename T>
    void Push(unsigned int count){
        static_assert(always_false<T>);
    }
};

template<>
void VertexBufferLayout::Push<float>(unsigned int count){
    elements.push_back(VertexLayoutElement(count, GL_FLOAT));
    stride+=count*sizeof(float);
}