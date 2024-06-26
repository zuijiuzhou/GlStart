
#include "PixelBuffer.h"

#include <map>

#include "State.h"
#include "GraphicContext.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(PixelBuffer, Buffer);

    struct PixelBuffer::Data
    {
        std::map<int, bool> dirties;
    };

    PixelBuffer::PixelBuffer() : d(new Data())
    {
    }
}