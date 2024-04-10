#include "Shape.h"

namespace AnyRenderer
{
    void Shape::setShader(Shader *shader)
    {
        shader_ = shader;
    }

    Shader *Shape::getShader() const
    {
        return shader_;
    }
}