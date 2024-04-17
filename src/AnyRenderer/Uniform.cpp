#include "Uniform.h"
#include "RenderContext.h"

namespace AnyRenderer
{

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

    void Uniform::apply(RenderContext &ctx) const
    {
        auto shader = ctx.getCurrentShader();
        if (shader)
        {
        }
    }
}