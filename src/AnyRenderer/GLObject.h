#pragma once
#include <glad/glad.h>
#include "Object.h"

namespace AnyRenderer
{
    class RenderContext;
    class GLObject : public Object
    {
        friend class RenderContext;

    public:
        GLObject();
        virtual ~GLObject();

    public:
        GLuint getId(RenderContext &ctx) const;
        bool isCreated(RenderContext &ctx) const;

    protected:
        void create(RenderContext &ctx);
        virtual GLuint onCreate(RenderContext &ctx) = 0;
        void release(RenderContext &ctx);
        virtual void onRelease(RenderContext &ctx) = 0;

    private:
        struct Data;
        Data *const d;
    };
}