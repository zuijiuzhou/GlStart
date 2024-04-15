#pragma once
#include <string>
#include "StateAttribute.h"
namespace AnyRenderer
{
    class Uniform : StateAttribute
    {
    public:
        Uniform(const std::string &name, int val);

    public:
        virtual void apply(const RenderContext &ctx) const override;

    private:
        std::string name_;
        int int_val_ = 0;
    };
}