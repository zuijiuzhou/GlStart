#include "DataBuffer.h"

#include <map>

#include "State.h"
#include "GraphicContext.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(DataBuffer, Buffer);

    struct DataBuffer::Data
    {
        std::map<int, bool> dirties;
    };

    DataBuffer::DataBuffer() : d(new Data())
    {
    }
}