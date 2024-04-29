#include "GraphicContext.h"
#include <queue>
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
        std::queue<RefPtr<Event>> event_queue;
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

    int GraphicContext::getWidth() const
    {
        return 0;
    }
    
    int GraphicContext::getHeight() const
    {
        return 0;
    }

    void GraphicContext::notify(Event *e)
    {
        d->event_queue.push(e);
    }
}