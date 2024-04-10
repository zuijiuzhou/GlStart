#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 color;
layout(location=3) in vec3 tex_coord;

uniform mat4 mvp;

out vec4 frag_color;

void main(){
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    frag_color = color;
}