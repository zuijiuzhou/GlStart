#include "Uniform.h"
#include "State.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(Uniform, StateAttribute);

    struct Uniform::Data
    {
        std::string name;
        int int_val;
    };

    Uniform::Uniform() : d(new Data())
    {
    }

    Uniform::Uniform(const std::string &name, int val) : Uniform()
    {
        d->name = name;
        d->int_val = val;
    }

    Uniform::~Uniform()
    {
        delete d;
    }

    void Uniform::apply(State &ctx) const
    {
        auto shader = ctx.getCurrentShader();
        if (shader)
        {
        }
    }
}