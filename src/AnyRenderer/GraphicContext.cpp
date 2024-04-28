#include "GraphicContext.h"
#include "ResourceManager.h"
#include "RefPtr.h"
#include "State.h"

namespace AnyRenderer
{
    struct GraphicContext::Data
    {
        static int max_id;
        int id = 0;
        RefPtr<State> state;
    };

    int GraphicContext::Data::max_id = 0;

    GraphicContext::GraphicContext() : d(new Data())
    {

        d->id = ++Data::max_id;
        d->state = new State(this);
    }

    GraphicContext::~GraphicContext()
    {
        delete d;
    }

    int GraphicContext::getId() const
    {
        return d->id;
    }

    void GraphicContext::makeCurrent()
    {
    }

    State *GraphicContext::getState() const
    {
        return d->state.get();
    }

    GraphicContext *GraphicContext::getContextById(int id)
    {
        return nullptr;
    }
}