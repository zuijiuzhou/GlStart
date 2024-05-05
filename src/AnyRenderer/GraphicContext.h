#pragma once
#include "Object.h"
#include "Event.h"

namespace AnyRenderer
{
    class State;

    class GraphicContext : public Object
    {
        friend class Renderer;

    public:
        class EventQueue : public Object
        {
        public:
            EventQueue();

        public:
            void push(Event *e);
            Event *pop();
            void clear();
            int size() const;

        private:
            struct Data;
            Data *const d;
        };

    protected:
        GraphicContext();
        virtual ~GraphicContext();

    public:
        int getId() const;
        State *getState() const;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;

        virtual void realize();
        virtual bool isRealized() const;
        virtual void makeCurrent();
        virtual void swapBuffers();
        void notify(Event *e);
        EventQueue *getEventQueue() const;

    public:
        static GraphicContext *getContextById(int id);

    public:
        struct Data;

    private:
        Data *const d;
    };
}