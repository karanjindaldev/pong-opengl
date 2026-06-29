#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "ErrorHandling.hpp"
#include "Ball.hpp"

void frameBufferCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float& player1_y, float& player2_y, float deltaTime);

bool startGame = false;

int main(){
    if(glfwInit()!=GLFW_TRUE){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Pong", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    float deltaTime = 0.0f;
    float currentFrameTime = 0.0f;
    float lastFrameTime = 0.0f;

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, frameBufferCallback);
    
    if(!gladLoadGL(glfwGetProcAddress)){
        return -1;
    }

    float vertex_data[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    float player1_x_right = 0.98f;
    float player1_y = 0.0f;

    float player1_vertex_data[] = {
        -1.0f, -0.35f,
        -1.0f, 0.35f,
        -player1_x_right, -0.35f,
        -player1_x_right, 0.35f 
    };

    float player2_x_left = 0.98f;
    float player2_y = 0.0f;

    float player2_vertex_data[] = {
        1.0f, -0.35f,
        1.0f, 0.35f,
        player2_x_left, -0.35f,
        player2_x_left, 0.35f 
    };

    Ball ball;

    float ball_vertices[] = {
        ball.width/2, ball.height/2,
        ball.width/2, -ball.height/2,
        -ball.width/2, ball.height/2,
        -ball.width/2, -ball.height/2
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 1, 3
    };

    Renderer renderer(0, 0, 1280, 720);

    VertexBuffer player1_vbo(player1_vertex_data, sizeof(player1_vertex_data));
    VertexBuffer player2_vbo(player2_vertex_data, sizeof(player2_vertex_data));
    VertexBuffer ball_vbo(ball_vertices, sizeof(ball_vertices));
    IndexBuffer ibo(indices, sizeof(indices));
    
    VertexBufferLayout layout;
    layout.Push<float>(2);

    VertexArray player1_vao;
    player1_vao.AddBuffersAndLayout(player1_vbo, ibo, layout);

    VertexArray player2_vao;
    player2_vao.AddBuffersAndLayout(player2_vbo, ibo, layout);

    VertexArray ball_vao;
    ball_vao.AddBuffersAndLayout(ball_vbo, ibo, layout);

    Shader shader("../res/shaders/basic.vert.glsl", "../res/shaders/basic.frag.glsl");
    
    while(!glfwWindowShouldClose(window)){
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glfwPollEvents();
        processInput(window, player1_y, player2_y, deltaTime);
        
        if(startGame){
            ball.Move(deltaTime);
        }

        ball.AABBCollision(-player1_x_right, player1_y+0.35f, player1_y-0.35f, true);
        ball.AABBCollision(player2_x_left, player2_y+0.35f, player2_y-0.35f, false);
        ball.DetectWallCollision();

        Renderer::ClearScreen();

        shader.SetUniform2f("offset", 0.0f, player1_y);
        renderer.Draw(player1_vao, shader);

        shader.SetUniform2f("offset", 0.0f, player2_y);
        renderer.Draw(player2_vao, shader);

        shader.SetUniform2f("offset", ball.X, ball.Y);
        renderer.Draw(ball_vao, shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}

void frameBufferCallback(GLFWwindow* window, int width, int height){
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glViewport(viewport[0], viewport[1], width, height);
}

void processInput(GLFWwindow* window, float& player1_y, float& player2_y, float deltaTime){
    if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS){
        startGame = true;
    }
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){
        player1_y+=1.0f*deltaTime;
    }
    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        player2_y+=1.0f*deltaTime;
    }
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){
        player1_y-=1.0f*deltaTime;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        player2_y-=1.0f*deltaTime;
    }

    player1_y = std::min(std::max(player1_y, -0.65f), 0.65f);
    player2_y = std::min(std::max(player2_y, -0.65f), 0.65f);
}