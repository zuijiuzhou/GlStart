#include "FrameBufferObject.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(FrameBufferObject, GLObject);

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