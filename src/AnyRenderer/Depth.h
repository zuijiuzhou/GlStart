
#pragma once

#include <glad/glad.h>
#include "StateAttribute.h"
namespace AnyRenderer
{
    class Depth : public StateAttribute
    {
    public:
        enum Func
        {
            NEVER = GL_NEVER,
            LESS = GL_LESS,
            EQUAL = GL_EQUAL,
            LEQUAL = GL_LEQUAL,
            GREATER = GL_GREATER,
            NOTEQUAL = GL_NOTEQUAL,
            GEQUAL = GL_GEQUAL,
            ALWAYS = GL_ALWAYS
        };

    public:
        Depth(double near, double far, Func func = LESS, bool mask = true);

    public:
        virtual Type getType() const;

    protected:
        virtual void apply(State &state) const;

        virtual void restore(State &state) const;

    private:
        struct Data;
        Data *const d;
    };
}