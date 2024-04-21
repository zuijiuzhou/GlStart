#include "SkyBox.h"
#include "CubeMap.h"
#include "Geometry.h"
#include "Shader.h"
#include "Model.h"
#include "StateSet.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    namespace
    {
        const char* sky_box_vs = R"(
#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec3 tex_coord;
uniform mat4 matrix_mvp;
out vec3 tex_coord;
void main(){
    gl_Position = matrix_mvp * vec4(position.x, position.y, position.z, 1.0);
    tex_coord = tex_coord;
}
        )";
        const char* sky_box_fs = R"(
#version 400 core
in uniform textureCube tex;
in vec3 frag_tex_coord;
out vec4 FragColor;
void main(){
    vec4 color = texture(tex, frag_tex_coord);
    FragColor = color;
}
        )";

        struct SkyBoxUpdateCallback : public ModelCallback{
            
            RefPtr<Shader> shader;
            
        };
    }

    Geometry *createSkyBox(CubeMap *tex)
    {
        auto cube = Geometry::createCube(2, 0, -1, -1, 1);
        cube->addTexture(0, tex);

        auto shader = new Shader(sky_box_vs, nullptr, sky_box_fs);
        
        auto model = new Model();
        model->getStateSet()->setShader(shader);
        model->addDrawable(cube);

    }
}