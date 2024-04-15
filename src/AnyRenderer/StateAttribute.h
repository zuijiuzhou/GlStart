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
            ATTR_UNIFORM,
            ATTR_LIGHTS
        };

    public:
        virtual void apply(const RenderContext &ctx) const = 0;

        virtual Type getType() const = 0;
    };
}