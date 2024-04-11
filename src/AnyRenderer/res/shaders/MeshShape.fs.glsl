#version 400 core
// #extension GL_ARB_explicit_uniform_location : enable

// layout(location = 0) uniform sampler2D tex_2d;

uniform sampler2D tex;
uniform samplerCube envmap;
uniform mat4 view_matrix;

in vec4 frag_color;
in vec2 frag_tex_coord;
in vec3 frag_envmap_coord;

out vec4 FragColor;

void main(){
    vec4 color = texture(tex, frag_tex_coord);
    FragColor = color;
}