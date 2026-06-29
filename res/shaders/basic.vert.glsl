#version 460 core
layout (location=0) in vec2 pos;

uniform float y = 0.0f;

void main(){
    gl_Position = vec4(pos.x, pos.y+y, 0.0f, 1.0f);
}