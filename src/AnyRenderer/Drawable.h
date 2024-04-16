#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "Object.h"
namespace AnyRenderer
{
    class RenderContext;
    class StateSet;
    class Shader;
    class Drawable : public Object
    {
    public:
        virtual void draw(const RenderContext &ctx) = 0;
    };
}