#pragma once
#include "GLObject.h"

namespace AnyRenderer
{
    class FrameBufferObject : public GLObject
    {
    public:
        FrameBufferObject();
        virtual ~FrameBufferObject();

    public:
    private:
        struct Data;
        Data *const d;
    };
}