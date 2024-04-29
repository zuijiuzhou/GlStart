#pragma once
#include "Object.h"
#include "Event.h"

namespace AnyRenderer
{
    class State;

    class GraphicContext : public Object
    {
        friend class Renderer;

    protected:
        GraphicContext();
        virtual ~GraphicContext();

    public:
        int getId() const;
        State* getState() const;
        virtual void makeCurrent();

        virtual int getWidth() const;
        virtual int getHeight() const;

        void notify(Event* e);

    public:
        static GraphicContext *getContextById(int id);

    public:
        struct Data;

    private:
        Data *const d;
    };
}