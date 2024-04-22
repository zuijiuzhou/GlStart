#include "Renderer.h"
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include "Utilities/Resources.h"
#include "Model.h"
#include "Drawable.h"
#include "Shader.h"
#include "StateSet.h"
#include "RenderContext.h"
#include "Camera.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct Renderer::Data
    {
        RefPtr<Camera> camera;
        RefPtr<RenderContext> ctx;
        std::vector<RefPtr<Model>> models;
        std::vector<RefPtr<Shader>> shaders;
        BoundingBox bb;
        bool is_initialized;
    };

    Renderer::Renderer() : d(new Data())
    {
        auto cam = new Camera();
        auto ctx = new RenderContext(cam);

        d->ctx = ctx;
        d->camera = cam;
    }

    Renderer::~Renderer()
    {
        delete d;
    }

    void Renderer::initialize()
    {
        d->is_initialized = true;
    }

    void Renderer::frame()
    {
        d->camera->apply();
        auto matrix_v = d->camera->getViewMatrix();
        auto matrix_vp = d->camera->getViewProjectionMatrix();
        auto view_dir = d->camera->getViewDir();
        auto &ctx = *d->ctx;
        for (auto model : d->models)
        {
            auto matrix_m = model->getMatrix();
            auto stateset = model->getStateSet();
            if (stateset)
            {
                stateset->apply(ctx);
                auto shader = ctx.getCurrentShader();
                if (shader)
                {
                    shader->set("matrix_m", matrix_m);
                    shader->set("matrix_v", matrix_v);
                    shader->set("matrix_mv", matrix_v * matrix_m);
                    shader->set("matrix_mvp",  matrix_vp * matrix_m);
                    shader->set("view_dir", view_dir);
                }
            }
            model->update(*d->ctx);
            for (int i = 0; i < model->getNbDrawables(); i++)
            {
                auto drawable = model->getDrawableAt(i);
                drawable->draw(ctx);
            }
        }
    }

    void Renderer::addModel(Model *model)
    {
        if (std::find(d->models.begin(), d->models.end(), model) == d->models.end())
        {
            d->models.push_back(model);
        }
    }

    Camera *Renderer::getCamera() const
    {
        return d->camera.get();
    }
}