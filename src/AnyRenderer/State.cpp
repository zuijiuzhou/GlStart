#include "State.h"

#include <set>

#include <vine/core/Ptr.h>

#include "GLObject.h"
#include "StateSet.h"
#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"
#include "GraphicContext.h"

namespace AnyRenderer
{
    namespace
    {
        struct StateData
        {
            vine::RefPtr<GraphicContext> ctx = nullptr;
            vine::RefPtr<Shader> current_shader = nullptr;
            vine::RefPtr<Camera> current_camera = nullptr;
            vine::RefPtr<Renderer> current_renderer = nullptr;

            std::set<vine::RefPtr<GLObject>> gl_objs;
        };
    }

    VI_OBJECT_META_IMPL(State, Object);

    struct State::Data : public StateData
    {
    };

    extern void state_set_current_camera(void* data, Camera *cam)
    {
        // State::Data 无成员，因此可以强转
        auto d = (StateData*)(data);
        d->current_camera = cam;
    }

    State::State(GraphicContext *ctx) : d(new Data())
    {
        d->ctx = ctx;
    }

    State::~State()
    {
        delete d;
    }

    GraphicContext *State::getContext() const
    {
        return d->ctx.get();
    }

    Shader *State::getCurrentShader() const
    {
        return d->current_shader.get();
    }

    Renderer *State::getCurrentRenderer() const
    {
        return d->current_renderer.get();
    }

    Camera *State::getCurrentCamera() const
    {
        return d->current_camera.get();
    }

    void State::applyShader(StateSet *ss)
    {
        d->current_shader = ss->getShader();
        if (d->current_shader.get())
        {
            d->current_shader->use(*this);
        }
    }

    void State::applyAttributes(StateSet *ss)
    {
        auto nb_attrs = ss->getNbAttributes();
        for (size_t i = 0; i < nb_attrs; i++)
        {
            ss->getAttributeAt(i)->apply(*this);
        }
    }

    void State::restoreAttributes(StateSet *ss)
    {
        auto nb_attrs = ss->getNbAttributes();
        for (size_t i = 0; i < nb_attrs; i++)
        {
            ss->getAttributeAt(i)->restore(*this);
        }
    }

    void State::attachGLObject(GLObject *obj)
    {
        if (!d->gl_objs.contains(obj))
        {
            d->gl_objs.insert(obj);
        }
    }

    void State::detachGLObject(GLObject *obj)
    {
        d->gl_objs.erase(obj);
    }

    void State::releaseGLObjects()
    {
        d->ctx->makeCurrent();
        while (!d->gl_objs.empty())
        {
            d->gl_objs.begin()->get()->release(*this);
        }
    }
}