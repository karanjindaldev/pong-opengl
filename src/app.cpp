#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "ErrorHandling.hpp"

int main(){
    if(glfwInit()!=GLFW_TRUE){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1000, 500, "Pong", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGL(glfwGetProcAddress)){
        return -1;
    }

    float vertex_data[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    
    // GLLog(glGetString(0x1234));

    Renderer renderer(0, 0, 1000, 500);

    VertexBuffer vbo(vertex_data, sizeof(vertex_data));
    VertexBufferLayout layout;

    layout.Push<float>(2);

    VertexArray vao;
    vao.AddBufferAndLayout(vbo, layout);

    Shader shader("../res/shaders/basic.vert.glsl", "../res/shaders/basic.frag.glsl");

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        renderer.Draw(vao, shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}