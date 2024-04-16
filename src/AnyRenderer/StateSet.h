#pragma once
#include <map>
#include "Object.h"
#include "StateAttribute.h"

namespace AnyRenderer
{
    class StateAttribute;
    class Shader;
    class RenderContext;
    class StateSet : public Object
    {
    public:
        void setAttribute(StateAttribute *attr);

        StateAttribute* getAttribute(StateAttribute::Type type) const;

        Shader* getShader() const;

        void setShader(Shader* shader);

        void apply(RenderContext &ctx) const;

    private:
        std::map<StateAttribute::Type, StateAttribute*> state_attrs;
        Shader* shader_ = nullptr;
    };
}