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

    void Draw(const VertexArray& vao, const Shader& shader, bool WIREFRAME_MODE=0) const {
        glPolygonMode(GL_FRONT_AND_BACK, WIREFRAME_MODE ? GL_LINE : GL_FILL);
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.Bind();
        shader.Bind();
        glDrawArrays(GL_TRIANGLES, 0, vao.vertexCount);
    }

   void Draw(const VertexArray& vao, const Shader& shader, const IndexBuffer& ibo, bool WIREFRAME_MODE=0) const {
        glPolygonMode(GL_FRONT_AND_BACK, WIREFRAME_MODE ? GL_LINE : GL_FILL);
        glClearColor(0.10f, 0.10f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ibo.Bind();
        vao.Bind();
        shader.Bind();
        glDrawElements(GL_TRIANGLES, ibo.count, GL_UNSIGNED_INT, nullptr);
    }
};