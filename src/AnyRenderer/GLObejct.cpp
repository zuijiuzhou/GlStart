#include "GLObject.h"
#include <map>
#include "RenderContext.h"

namespace AnyRenderer
{
    struct GLObject::Data
    {
        std::map<int, GLuint> ids;
    };

    GLObject::GLObject() : d(new Data())
    {
    }
    GLObject::~GLObject()
    {
        delete d;
    }
    GLuint GLObject::getId(RenderContext & ctx) const
    {
        auto ctx_id = ctx.getContextId();
        if (d->ids.contains(ctx_id))
        {
            return d->ids[ctx_id];
        }
        return 0;
    }

    bool GLObject::isCreated(RenderContext & ctx) const
    {
        auto ctx_id = ctx.getContextId();
        return d->ids.contains(ctx_id);
    }

    void GLObject::create(RenderContext & ctx)
    {
        if (isCreated(ctx))
            return;
        auto id = onCreate(ctx);
        d->ids.insert({ctx.getContextId(), id});
    }

    void GLObject::release(RenderContext& ctx){
        if(isCreated(ctx)){
            onRelease(ctx);
            d->ids.erase(ctx.getContextId());
        }
    }

}