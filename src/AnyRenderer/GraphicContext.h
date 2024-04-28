#pragma once
#include "Object.h"

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

    public:
        static GraphicContext *getContextById(int id);

    public:
        struct Data;

    private:
        Data *const d;
    };
}