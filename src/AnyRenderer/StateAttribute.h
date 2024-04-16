#pragma once
#include "Object.h"
namespace AnyRenderer
{
    class RenderContext;
    class StateAttribute : public Object
    {
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
        virtual void apply(RenderContext &ctx) const = 0;

        virtual Type getType() const = 0;
    };
}