#include "GLObject.h"
#include <map>
#include "State.h"
#include "GraphicContext.h"

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
    GLuint GLObject::getId(State & state) const
    {
        auto ctx_id = state.getContext()->getId();
        if (d->ids.contains(ctx_id))
        {
            return d->ids[ctx_id];
        }
        return 0;
    }

    bool GLObject::isCreated(State & state) const
    {
        auto ctx_id = state.getContext()->getId();
        return d->ids.contains(ctx_id);
    }

    void GLObject::create(State & state)
    {
        if (isCreated(state))
            return;
        auto id = onCreate(state);
        d->ids.insert({state.getContext()->getId(), id});
        state.attachGLObject(this);
    }

    void GLObject::release(State& state){
        if(isCreated(state)){
            onRelease(state);
            d->ids.erase(state.getContext()->getId());
            state.detachGLObject(this);
        }
    }

}