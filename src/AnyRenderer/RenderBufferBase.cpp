
#include "RenderBufferBase.h"

#include <map>

#include "State.h"
#include "GraphicContext.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(RenderBufferBase, Buffer);

    struct RenderBufferBase::Data
    {
        std::map<int, bool> dirties;
    };

    RenderBufferBase::RenderBufferBase() : d(new Data())
    {

    }
}