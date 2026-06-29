#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "ErrorHandling.hpp"

void frameBufferCallback(GLFWwindow*, int, int);

int main(){
    if(glfwInit()!=GLFW_TRUE){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Pong", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, frameBufferCallback);
    
    if(!gladLoadGL(glfwGetProcAddress)){
        return -1;
    }

    float vertex_data[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    float player1_vertex_data[] = {
        -1.0f, -0.35f,
        -1.0f, 0.35f,
        -0.98f, -0.35f,
        -0.98f, 0.35f 
    };

    float player2_vertex_data[] = {
        1.0f, -0.35f,
        1.0f, 0.35f,
        0.98f, -0.35f,
        0.98f, 0.35f 
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3
    };

    Renderer renderer(0, 0, 1280, 720);

    VertexBuffer player1_vbo(player1_vertex_data, sizeof(player1_vertex_data));
    VertexBuffer player2_vbo(player2_vertex_data, sizeof(player2_vertex_data));
    IndexBuffer ibo(indices, sizeof(indices));
    
    VertexBufferLayout layout;
    layout.Push<float>(2);

    VertexArray player1_vao;
    player1_vao.AddBuffersAndLayout(player1_vbo, ibo, layout);

    VertexArray player2_vao;
    player2_vao.AddBuffersAndLayout(player2_vbo, ibo, layout);

    Shader shader("../res/shaders/basic.vert.glsl", "../res/shaders/basic.frag.glsl");

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        Renderer::ClearScreen();
        renderer.Draw(player1_vao, shader);
        renderer.Draw(player2_vao, shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void frameBufferCallback(GLFWwindow* window, int width, int height){
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(viewport[0], viewport[1], width, height);
}