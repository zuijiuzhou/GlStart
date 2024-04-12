#include "BufferData.h"

namespace AnyRenderer
{
    void BufferData::update()
    {
        is_dirty_ = onUpdate();
    }

    void BufferData::bind()
    {
        if (!isCreated())
            create();
        if (!isCreated())
            return;
        if (isDirty())
            update();
        onBind();
    }

    void BufferData::unbind()
    {
        if (!isCreated())
            return;
        onUnbind();
    }

    bool BufferData::isDirty() const
    {
        return is_dirty_;
    }
    void BufferData::setDirty(bool dirty)
    {
        is_dirty_ = dirty;
    }
}