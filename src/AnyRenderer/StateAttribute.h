#pragma once
#include "Object.h"
namespace AnyRenderer
{
    class StateSet;
    class RenderContext;
    class StateAttribute : public Object
    {
        friend class StateSet;

    public:
        enum Type
        {
            ATTR_MATERIAL,
            ATTR_DEPTH,
            ATTR_LIGHTING,
            ATTR_SPOT_LIGHTS,
            ATTR_DIRECTIONAL_LIGHTS,
            ATTR_LIGHTS,
            ATTR_SHADER
        };

    public:
        virtual Type getType() const = 0;

    protected:
        virtual void apply(RenderContext &ctx) const = 0;

        virtual void restore(RenderContext &ctx) const;
    };
}