#include "Drawable.h"
#include "StateSet.h"
#include "Shader.h"

namespace AnyRenderer
{

    Drawable::~Drawable()
    {
        if (shader_)
            shader_->unref();
        if (state_set_)
            state_set_->unref();
    }

    void Drawable::setShader(Shader *shader)
    {
        if (shader_)
            shader_->unref();
        shader_ = shader;
        if (shader_)
            shader_->ref();
    }

    Shader *Drawable::getShader() const
    {
        return shader_;
    }

    StateSet *Drawable::getOrCreateStateSet()
    {
        if (!state_set_)
        {
            state_set_ = new StateSet();
            state_set_->ref();
        }
        return state_set_;
    }

    StateSet *Drawable::getStateSet()
    {
        return state_set_;
    }
}