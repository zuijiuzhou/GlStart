#version 330 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec4 color;

uniform mat4 matrix_m;
uniform mat4 matrix_v;
uniform mat4 matrix_mv;
uniform mat4 matrix_mvp;

out vec4 frag_color;
out vec3 frag_world_posi;
out vec3 frag_world_norm;

void main(){
    gl_Position = matrix_mvp * vec4(position.x, position.y, position.z, 1.0);
    frag_color = color;

    frag_world_posi = mat3(matrix_m) * position;
    frag_world_norm = mat3(matrix_m) * normal;
}