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

    void Renderer::setContext(RenderContext *ctx)
    {
        if (d->is_initialized)
            throw std::exception();
        d->ctx = ctx;
    }

    void Renderer::initialize()
    {
        if (d->is_initialized)
        {
            return;
        }
        d->ctx->makeCurrent();
        glDepthMask(GL_TRUE);
        d->is_initialized = true;
    }

    bool Renderer::isInitialized() const
    {
        return d->is_initialized;
    }

    void Renderer::frame()
    {
        if (!d->is_initialized)
            return;
        d->ctx->makeCurrent();
        d->camera->apply();

        glDepthRange(0.0, 1.0);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        auto matrix_v = d->camera->getViewMatrix();
        auto matrix_vp = d->camera->getViewProjectionMatrix();
        auto view_dir = d->camera->getViewDir();
        auto &ctx = *d->ctx;
        for (auto model : d->models)
        {
            auto stateset = model->getStateSet();
            if (stateset)
            {
                stateset->applyShader(ctx);
            }
            model->update(ctx);
            auto matrix_m = model->getMatrix();
            if (stateset)
            {
                stateset->apply(ctx);
                auto shader = ctx.getCurrentShader();
                if (shader)
                {
                    shader->set(ctx, "matrix_m", matrix_m);
                    shader->set(ctx, "matrix_v", matrix_v);
                    shader->set(ctx, "matrix_mv", matrix_v * matrix_m);
                    shader->set(ctx, "matrix_mvp", matrix_vp * matrix_m);
                    shader->set(ctx, "view_dir", view_dir);
                }
            }
            for (int i = 0; i < model->getNbDrawables(); i++)
            {
                auto drawable = model->getDrawableAt(i);
                drawable->draw(ctx);
            }
            if (stateset)
            {
                stateset->restore(ctx);
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