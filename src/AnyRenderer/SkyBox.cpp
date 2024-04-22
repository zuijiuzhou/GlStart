#include "SkyBox.h"
#include "CubeMap.h"
#include "Geometry.h"
#include "Shader.h"
#include "Model.h"
#include "StateSet.h"
#include "RefPtr.h"
#include "RenderContext.h"
#include "Camera.h"

namespace AnyRenderer
{
    namespace
    {
        const char *sky_box_vs = R"(
#version 330 core
layout(location=0) in vec3 position;
uniform mat4 matrix_mvp;
out vec3 frag_tex_coord;
void main(){
    gl_Position = matrix_mvp * vec4(position.x, position.y, position.z, 1.0);
    frag_tex_coord = position;
}
        )";
        const char *sky_box_fs = R"(
#version 330 core
uniform samplerCube tex;
in vec3 frag_tex_coord;
out vec4 FragColor;
void main(){
    vec4 color = texture(tex, frag_tex_coord);
    FragColor = color;
}
        )";

        struct SkyBoxUpdateCallback : public ModelCallback
        {
            SkyBoxUpdateCallback() : ModelCallback(UPDATE) {}
            virtual void operator()(const RenderContext &ctx, Model *model) override
            {
                auto shader = ctx.getCurrentShader();
                auto cam = ctx.getCamera();
                auto mat_v = cam->getViewMatrix();
                mat_v[3] = glm::vec4(0.f, 0.f, 0.f, 1.f);
                glm::mat4 m1(1.);
                m1 = glm::rotate(m1, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
                auto mat_p = cam->getProjectionMatrix();

                shader->set("matrix_mvp", mat_p * mat_v *m1);
            }
        };
    }

    Model *createSkyBox(CubeMap *tex)
    {
        auto cube = Geometry::createCube(1000, 0, -1, -1, -1);
        cube->addTexture(0, "tex", tex);
        auto shader = new Shader(sky_box_vs, {}, sky_box_fs);
        auto model = new Model();
        model->getOrCreateStateSet()->setShader(shader);
        model->addDrawable(cube);
        model->addCallback(new SkyBoxUpdateCallback());
        return model;
    }
}