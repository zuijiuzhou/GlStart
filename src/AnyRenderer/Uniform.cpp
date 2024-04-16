#include "Uniform.h"
#include "RenderContext.h"

namespace AnyRenderer
{
    Uniform::Uniform(const std::string &name, int val)
        : name_(name), int_val_(val)
    {
    }

    void Uniform::apply(RenderContext &ctx) const
    {
        auto shader = ctx.getCurrentShader();
        if(shader){
            
        }
    }
}