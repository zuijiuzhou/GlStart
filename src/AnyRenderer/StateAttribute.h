#pragma once
#include "Object.h"
namespace AnyRenderer
{
    class StateSet;
    class State;
    class StateAttribute : public Object
    {
        friend class State;

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
        virtual void apply(State &state) const = 0;

        virtual void restore(State &state) const;
    };
}