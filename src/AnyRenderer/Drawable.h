#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "Object.h"
#include "BoundingBox.h"
namespace AnyRenderer
{
    class Shader;
    class StateSet;
    class State;
    class Drawable : public Object
    {
        VI_OBJECT_META;

    public:
        virtual void draw(State &ctx) = 0;
        
        virtual BoundingBox getBoundingBox() const = 0;
    };
}