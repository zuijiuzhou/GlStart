#version 400 core
#define MAX_LIGHT 8
// #extension GL_ARB_explicit_uniform_location : enable

// layout(location = 0) uniform sampler2D tex_2d;
struct Material{
    vec4 a;
    vec4 d;
    vec4 s;
    vec4 e;
    float sh;
};

struct Light{
    // Common
    vec4 a;
    vec4 d;
    vec4 s;
    vec3 dir;

    // Spot
    vec4 pos;
    float cuto;
    float expo;

    float k_c;
    float k_l;
    float k_q;
};

uniform sampler2D tex_2d;
uniform Material mate;
uniform Light lights[MAX_LIGHT];
uniform int lights_count = 0;
uniform vec3 view_dir;

in vec4 frag_color;
in vec2 frag_tex_coord;
in vec3 frag_world_posi;
in vec3 frag_world_norm;

out vec4 FragColor;

vec3 get_directional_light_contribution(Light l, Material m, vec3 view_dir, vec3 frag_norm){
   vec3 a = l.a.rgb * m.a.rgb;
   vec3 d = max(dot(l.dir, frag_norm), 0) * m.d.rgb;

   return a + d;
}

vec4 get_sopt_light_contribution(Light l, Material m, vec3 frag_posi, vec3 frag_norm){
   vec4 a = l.a * m.a;
   vec4 d = max(dot(l.dir, frag_norm), 0) * m.d;

   return a + d;
}

void main(){

    vec4 color = texture(tex_2d, frag_tex_coord);
    if(lights_count > 0){
        vec3 c = vec3(0, 0, 0);
        for(int i = 0; i < lights_count; i++){
            if(i >= MAX_LIGHT)
                break;
            Light l = lights[i];
            c += get_directional_light_contribution(l, mate, view_dir, frag_world_norm);
        }
        color = vec4(c, 1.0);
    }
    FragColor = color;
}