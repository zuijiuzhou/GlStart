#include "FrameBufferObject.h"

namespace AnyRenderer
{

    struct FrameBufferObject::Data
    {
    };

    FrameBufferObject::FrameBufferObject() : d(new Data())
    {
    }
    FrameBufferObject::~FrameBufferObject()
    {
    }
}