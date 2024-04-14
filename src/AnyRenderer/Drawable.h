#pragma once
#include <glad/glad.h>
namespace AnyRenderer
{
    class RenderContext;
    class StateSet;
    class Shader;
    class Drawable
    {
        public:
        virtual ~Drawable();
    public:
        virtual void preDraw(const RenderContext& ctx);

        virtual void draw(const RenderContext& ctx) = 0;

        virtual void postDraw(const RenderContext& ctx);

        void setShader(Shader *shader);

        virtual Shader *getShader() const;

        StateSet* getOrCreateState();

    private:
        Shader* shader_ = nullptr;
        StateSet* state_set_ = nullptr;

    };
}