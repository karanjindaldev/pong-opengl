#version 460 core
layout (location=0) in vec2 pos;

uniform vec2 offset = vec2(0.0f, 0.0f);

void main(){
    gl_Position = vec4(pos.x+offset.x, pos.y+offset.y, 0.0f, 1.0f);
}