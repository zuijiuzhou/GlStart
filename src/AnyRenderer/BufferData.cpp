#include "BufferData.h"
#include <map>
#include "State.h"
#include "GraphicContext.h"

namespace AnyRenderer
{
    struct BufferData::Data
    {
        std::map<int, bool> dirties;
    };

    BufferData::BufferData() : d(new Data())
    {
    }

    void BufferData::update(State &state)
    {
        auto ctx_id = state.getContext()->getId();
        if (isDirty(state))
        {
            auto status = onUpdate(state);
            d->dirties[ctx_id] = status;
        }
    }

    void BufferData::bind(State &state)
    {
        if (!isCreated(state))
            create(state);
        if (!isCreated(state))
            return;
        if (isDirty(state))
            update(state);
        onBind(state);
    }

    void BufferData::unbind(State &state)
    {
        if (!isCreated(state))
            return;
        onUnbind(state);
    }

    bool BufferData::isDirty(State &state) const
    {
        auto ctx_id = state.getContext()->getId();
        if (d->dirties.contains(ctx_id))
        {
            return d->dirties[ctx_id];
        }
        return false;
    }
    void BufferData::dirty()
    {
        for (auto &kv : d->dirties)
        {
            kv.second = true;
        }
    }
}