#pragma once
#include "GLObject.h"

namespace AnyRenderer
{
    class FrameBufferObject : public GLObject
    {
        VI_OBJECT_META;

    public:
        FrameBufferObject();
        virtual ~FrameBufferObject();

    public:
    private:
        struct Data;
        Data *const d;
    };
}