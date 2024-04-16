#pragma once

#include <glm/mat4x4.hpp>
#include "Object.h"
#include "BoundingBox.h"
namespace AnyRenderer
{
    class Drawable;
    class StateSet;
    class Node : public Object
    {
    public:
        virtual ~Node();

    public:
        glm::mat4 getMatrix() const;

        void setMatrix(const glm::mat4 &mat);

        StateSet *getOrCreateStateSet();

        StateSet *getStateSet();

        virtual BoundingBox getBoundingBox() const = 0;

    private:
        StateSet *state_set_ = nullptr;
        glm::mat4 matrix_ = glm::mat4(1.0);
    };
}