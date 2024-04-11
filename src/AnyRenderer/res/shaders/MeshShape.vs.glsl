#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec4 color;
layout(location=3) in vec3 tex_coord;
layout(location=4) in vec3 envmap_coord;

uniform mat4 mvp;

out vec4 frag_color;
out vec3 frag_tex_coord;
out vec3 frag_envmap_coord;

void main(){
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    frag_color = color;
    frag_tex_coord = tex_coord;
    frag_envmap_coord = envmap_coord;
}