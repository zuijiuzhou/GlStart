#pragma once
#include "anyrenderer_global.h"

namespace AnyRenderer
{
    class RenderContext;
    class Shader;
    class Shape
    {
    public:
        virtual void draw(const RenderContext& ctx) = 0;

        void setShader(Shader *shader);

        virtual Shader *getShader() const;

    private:
        Shader *shader_ = nullptr;
    };
}