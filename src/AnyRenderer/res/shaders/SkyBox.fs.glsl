
#version 400 core
uniform samplerCube tex;
in vec3 frag_tex_coord;
out vec4 FragColor;
void main(){
    vec4 color = texture(tex, frag_tex_coord);
    FragColor = color;
}
        