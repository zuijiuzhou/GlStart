#pragma once
#include <vector>
#include "Object.h"
namespace AnyRenderer
{
    class StateAttribute;
    class RenderContext;
    class StateSet : public Object
    {
    public:
        void setAttribute(StateAttribute *attr);

        void apply(const RenderContext &ctx)const;

    private:
        std::vector<StateAttribute *> state_attrs;
    };
}