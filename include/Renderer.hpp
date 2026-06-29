#pragma once

#include <glad/gl.h>

#include "VertexArray.hpp"
#include "Shader.hpp"

class Renderer{
public:
    Renderer(int x, int y, int width, int height){
        glViewport(x, y, width, height);
    }

    void Draw(const VertexArray& vao, const Shader& shader) const {
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.Bind();
        shader.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};