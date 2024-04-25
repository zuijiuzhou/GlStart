#include "BufferData.h"
#include <map>
#include "RenderContext.h"

namespace AnyRenderer
{
    struct BufferData::Data
    {
        std::map<int, bool> dirties;
    };

    BufferData::BufferData() : d(new Data())
    {
    }

    void BufferData::update(RenderContext &ctx)
    {
        auto ctx_id = ctx.getContextId();
        if (isDirty(ctx))
        {
            auto status = onUpdate(ctx);
            d->dirties[ctx_id] = status;
        }
    }

    void BufferData::bind(RenderContext &ctx)
    {
        if (!isCreated(ctx))
            create(ctx);
        if (!isCreated(ctx))
            return;
        if (isDirty(ctx))
            update(ctx);
        onBind(ctx);
    }

    void BufferData::unbind(RenderContext &ctx)
    {
        if (!isCreated(ctx))
            return;
        onUnbind(ctx);
    }

    bool BufferData::isDirty(RenderContext &ctx) const
    {
        auto ctx_id = ctx.getContextId();
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