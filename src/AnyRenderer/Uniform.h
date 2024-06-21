#pragma once
#include <string>
#include "StateAttribute.h"
namespace AnyRenderer
{
    class Uniform : StateAttribute
    {
        VI_OBJECT_META;

    public:
        Uniform();
        Uniform(const std::string &name, int val);

        virtual ~Uniform();

    public:
        virtual void apply(State &state) const override;

    private:
        VI_OBJECT_DATA;
    };
}