#include "StateSet.h"
#include "StateAttribute.h"
#include "RenderContext.h"
#include "Shader.h"

namespace AnyRenderer
{
    void StateSet::setAttribute(StateAttribute *attr)
    {
        if (!attr)
            return;
        auto type = attr->getType();
        auto found_at = state_attrs.find(type);
        if (found_at != state_attrs.end())
        {
            if (attr == found_at->second)
                return;
            found_at->second->unref();
            state_attrs.erase(found_at);
        }
        state_attrs.insert({attr->getType(), attr});
        attr->ref();
    }

    void StateSet::apply(RenderContext &ctx) const
    {
        if(shader_){
            ctx.current_shader_ = shader_;
            shader_->use();
        }
        for (auto &kv : state_attrs)
        {
            kv.second->apply(ctx);
        }
    }

    StateAttribute *StateSet::getAttribute(StateAttribute::Type type) const
    {
        auto found_at = state_attrs.find(type);
        if (found_at != state_attrs.end())
        {
            return found_at->second;
        }
        return nullptr;
    }

    Shader *StateSet::getShader() const
    {
        return shader_;
    }

    void StateSet::setShader(Shader *shader)
    {
        if (shader_ == shader)
            return;
        if (shader_)
            shader_->unref();
        shader_ = shader;
        if (shader_)
            shader_->ref();
    }
}