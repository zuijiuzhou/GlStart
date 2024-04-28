#include "Renderer.h"
#include <iostream>
#include <functional>
#include <glad/glad.h>
#include "Utilities/Resources.h"
#include "Model.h"
#include "Drawable.h"
#include "Shader.h"
#include "StateSet.h"
#include "GraphicContext.h"
#include "Camera.h"
#include "RefPtr.h"
#include "State.h"

namespace AnyRenderer
{
    extern void state_set_current_camera(void *data, Camera *cam);

    struct Renderer::Data
    {
        RefPtr<Camera> camera;
        RefPtr<GraphicContext> ctx;
        std::vector<RefPtr<Model>> models;
        std::vector<RefPtr<Shader>> shaders;
        BoundingBox bb;
        bool is_initialized;
    };

    Renderer::Renderer() : d(new Data())
    {
        auto cam = new Camera();
        auto ctx = new GraphicContext();

        d->ctx = ctx;
        d->camera = cam;
    }

    Renderer::~Renderer()
    {
        delete d;
    }

    void Renderer::setContext(GraphicContext *ctx)
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
        auto &state = *ctx.getState();
        for (auto model : d->models)
        {
            state_set_current_camera(state.d, d->camera.get());
            auto stateset = model->getStateSet();
            if (stateset)
            {
                state.applyShader(stateset);
            }
            model->update(state);
            auto matrix_m = model->getMatrix();
            if (stateset)
            {
                state.applyAttributes(stateset);
                auto shader = state.getCurrentShader();
                if (shader)
                {
                    shader->set(state, "matrix_m", matrix_m);
                    shader->set(state, "matrix_v", matrix_v);
                    shader->set(state, "matrix_mv", matrix_v * matrix_m);
                    shader->set(state, "matrix_mvp", matrix_vp * matrix_m);
                    shader->set(state, "view_dir", view_dir);
                }
            }
            for (int i = 0; i < model->getNbDrawables(); i++)
            {
                auto drawable = model->getDrawableAt(i);
                drawable->draw(state);
            }
            if (stateset)
            {
                state.restoreAttributes(stateset);
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