#pragma once
#include "GLObject.h"
namespace AnyRenderer
{
    class BufferData : public GLObject
    {
    public:
        BufferData();

    public:
        bool isDirty(RenderContext &ctx) const;
        void dirty();

        void bind(RenderContext &ctx);
        void unbind(RenderContext &ctx);
        void update(RenderContext &ctx);

    protected:
        virtual bool onUpdate(RenderContext &ctx) = 0;
        virtual void onBind(RenderContext &ctx) = 0;
        virtual void onUnbind(RenderContext &ctx) = 0;

    private:
        struct Data;
        Data *const d;
    };
}