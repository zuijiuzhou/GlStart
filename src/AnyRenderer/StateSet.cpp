#include "StateSet.h"
#include "StateAttribute.h"
#include "RenderContext.h"
#include "Shader.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    extern void RenderContext_set_shader(RenderContext::Data *d, Shader *shader);

    struct StateSet::Data
    {
        std::map<StateAttribute::Type, RefPtr<StateAttribute>> state_attrs;
        RefPtr<Shader> shader;
    };

    StateSet::StateSet() : d(new Data())
    {
    }
    StateSet::~StateSet()
    {
        delete d;
    }

    void StateSet::setAttribute(StateAttribute *attr)
    {
        if (!attr)
            return;
        auto type = attr->getType();
        auto found_at = d->state_attrs.find(type);
        if (found_at != d->state_attrs.end())
        {
            if (attr == found_at->second.get())
                return;
            d->state_attrs.erase(found_at);
        }
        d->state_attrs.insert({attr->getType(), attr});
    }

    void StateSet::applyShader(RenderContext &ctx) const
    {
        if (d->shader.valid())
        {
            RenderContext_set_shader(ctx.d, d->shader.get());
            d->shader->use(ctx);
        }
    }

    void StateSet::apply(RenderContext &ctx) const
    {
        for (auto &kv : d->state_attrs)
        {
            kv.second->apply(ctx);
        }
    }

    void StateSet::restore(RenderContext &ctx) const
    {
        for (auto &kv : d->state_attrs)
        {
            kv.second->restore(ctx);
        }
    }

    StateAttribute *StateSet::getAttribute(StateAttribute::Type type) const
    {
        auto found_at = d->state_attrs.find(type);
        if (found_at != d->state_attrs.end())
        {
            return found_at->second.get();
        }
        return nullptr;
    }

    Shader *StateSet::getShader() const
    {
        return d->shader.get();
    }

    void StateSet::setShader(Shader *shader)
    {
        if (d->shader == shader)
            return;
        d->shader = shader;
    }
}