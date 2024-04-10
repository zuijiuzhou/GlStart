#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

out vec4 color_rgba;
uniform vec4 rgba;
uniform mat4 mvp;

void main(){
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    color_rgba = rgba;
}