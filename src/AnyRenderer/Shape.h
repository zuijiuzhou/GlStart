#pragma once
#include <glad/glad.h>
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