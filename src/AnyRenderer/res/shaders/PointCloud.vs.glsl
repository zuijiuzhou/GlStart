#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 rgb;

out vec4 frag_color;
out int point_id;
uniform mat4 mvp;

void main(){
    gl_Position = mvp * vec4(position.x, position.y, position.z, 1.0);
    gl_PointSize = clamp(position.z * 10, 5, 20);
    frag_color = vec4(rgb.x, rgb.y, rgb.z, 1.0);
    point_id = gl_VertexID;
}