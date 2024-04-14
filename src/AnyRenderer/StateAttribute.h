#pragma once
#include "Object.h"
namespace AnyRenderer
{
    class StateAttribute : public Object
    {
    public:
        virtual void apply() const;
    };
}