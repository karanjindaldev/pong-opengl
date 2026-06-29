#pragma once

#include <glad/gl.h>
#include <iostream>

#define ASSERT(x) if(!(x)) __asm volatile("int $3")
#define GLLog(x) GLClearErrors();\
    x;\
    ASSERT(GLGetError(__FILE__, __LINE__));

void GLClearErrors(){
    while(glGetError());
}

bool GLGetError(const char* file, unsigned int line){
    unsigned int error = glGetError();
    if(error!=GL_NO_ERROR){
        std::cout<<"[OPENGL ERROR]: ("<<error<<") "<<file<<":"<<line<<'\n';
        return true;
    }
    return false;
}