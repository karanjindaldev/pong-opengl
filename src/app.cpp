#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(){
    if(glfwInit()!=GLFW_TRUE){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pong", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGL(glfwGetProcAddress)){
        return -1;
    }
    
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    glfwTerminate();
}