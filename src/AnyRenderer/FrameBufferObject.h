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
        VI_OBJECT_DATA;
    };
}