#pragma once
#include "GLObject.h"
namespace AnyRenderer
{
    class BufferData : public GLObject
    {
    public:
        bool isDirty() const;
        void setDirty(bool dirty);
        void bind();
        void unbind();

    protected:
        void update();
        virtual bool onUpdate() = 0;
        virtual void onBind() = 0;
        virtual void onUnbind() = 0;

    private:
        bool is_dirty_ = false;
    };
}