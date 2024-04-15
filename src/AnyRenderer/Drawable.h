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
        virtual void draw(const RenderContext& ctx) = 0;

        void setShader(Shader *shader);

        virtual Shader *getShader() const;

        StateSet* getOrCreateStateSet();
        StateSet* getStateSet();

    private:
        Shader* shader_ = nullptr;
        StateSet* state_set_ = nullptr;
    };
}