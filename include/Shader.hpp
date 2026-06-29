#pragma once

#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include <string>

class Shader{
private:
    unsigned int rendererID;

    unsigned int LoadAndCompileShader(const char* filepath, const unsigned int shaderType){
        std::ifstream file(filepath);

        try{
            file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            std::stringstream string_stream;
            std::string str;
            const char* shaderSource;
    
            string_stream << file.rdbuf();
            str = string_stream.str();
            shaderSource = str.c_str();
    
            file.close();
    
            unsigned int shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &shaderSource, nullptr);
            glCompileShader(shader);
            return shader;
        }
        catch(std::ios_base::failure& e){
            std::cout<<"File IO Error: "<<e.what()<<'\n';
        }
    }

public:
    Shader(const char* vs_filepath, const char* fs_filepath){
        unsigned int vs = LoadAndCompileShader(vs_filepath, GL_VERTEX_SHADER);
        unsigned int fs = LoadAndCompileShader(fs_filepath, GL_FRAGMENT_SHADER);

        this->rendererID = glCreateProgram();
        glAttachShader(this->rendererID, vs);
        glAttachShader(this->rendererID, fs);
        glLinkProgram(this->rendererID);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void Bind() const {
        glUseProgram(this->rendererID);
    }

    void Unbind() const {
        glUseProgram(0);
    }

    void SetUniform1f(const char* uniformName, float value) const {
        int location = glGetUniformLocation(this->rendererID, uniformName);
        if(location!=-1){
            glUniform1f(location, value);
        }
    }

    void SetUniform2f(const char* uniformName, float value1, float value2) const {
        int location = glGetUniformLocation(this->rendererID, uniformName);
        if(location!=-1){
            glUniform2f(location, value1, value2);
        }
    }

    ~Shader(){
        glDeleteProgram(this->rendererID);
    }
};