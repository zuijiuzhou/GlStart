#pragma once
#include <string>
#include "StateAttribute.h"
namespace AnyRenderer
{
    class Uniform : StateAttribute
    {
    public:
        Uniform();
        Uniform(const std::string &name, int val);

        virtual ~Uniform();

    public:
        virtual void apply(RenderContext &ctx) const override;

    private:
        struct Data;
        Data *const d;
    };
}