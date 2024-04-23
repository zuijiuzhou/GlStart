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
        StateSet();
        virtual ~StateSet();

    public:
        void setAttribute(StateAttribute *attr);

        StateAttribute *getAttribute(StateAttribute::Type type) const;

        Shader *getShader() const;

        void setShader(Shader *shader);

        void applyShader(RenderContext &ctx) const;

        void apply(RenderContext &ctx) const;

        void restore(RenderContext &ctx) const;

    private:
        struct Data;
        Data *const d;
    };
}