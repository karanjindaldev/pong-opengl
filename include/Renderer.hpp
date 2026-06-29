#pragma once

#include <glad/gl.h>

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "IndexBuffer.hpp"

class Renderer{
public:
    Renderer(int x, int y, int width, int height){
        glViewport(x, y, width, height);
    }

    static void ClearScreen(){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Draw(const VertexArray& vao, const Shader& shader, bool WIREFRAME_MODE=0) const {
        glPolygonMode(GL_FRONT_AND_BACK, WIREFRAME_MODE ? GL_LINE : GL_FILL);

        vao.Bind();
        shader.Bind();
        glDrawElements(GL_TRIANGLES, vao.indexCount, GL_UNSIGNED_INT, nullptr);
    }
};