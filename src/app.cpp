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

    float vertex_data_rectangle[] = {
        -1.0f, -0.35f,
        -1.0f, 0.35f,
        -0.98f, -0.35f,
        -0.98f, 0.35f 
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3
    };

    Renderer renderer(0, 0, 1280, 720);

    VertexBuffer vbo(vertex_data_rectangle, sizeof(vertex_data_rectangle));
    IndexBuffer ibo(indices, sizeof(indices));
    VertexBufferLayout layout;

    layout.Push<float>(2);

    VertexArray vao;
    vao.AddBufferAndLayout(vbo, layout);

    Shader shader("../res/shaders/basic.vert.glsl", "../res/shaders/basic.frag.glsl");

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        renderer.Draw(vao, shader, ibo);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void frameBufferCallback(GLFWwindow* window, int width, int height){
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(viewport[0], viewport[1], width, height);
}