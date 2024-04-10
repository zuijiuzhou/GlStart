#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 rgb;

out vec4 frag_color;
uniform mat4 mvp;

void main(){
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    gl_PointSize = position.z;
    frag_color = vec4(rgb.x, rgb.y, rgb.z, 1.0);
}