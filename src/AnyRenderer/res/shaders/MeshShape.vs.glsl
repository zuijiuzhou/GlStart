#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec4 color;
layout(location=3) in vec2 tex_coord;

uniform mat4 mvp;

out vec4 frag_color;
out vec2 frag_tex_coord;

void main(){
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    frag_color = color;
    frag_tex_coord = tex_coord;
}