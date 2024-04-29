#pragma once
#include "Object.h"
namespace AnyRenderer
{
    class GraphicContext;

    enum EventType
    {
        MousePress,
        MouseMove,
        MouseRelease,
        MouseWheel,
        Resize
    };

    enum MouseButton
    {
        ButtonNone,
        ButtonLeft = 1,
        ButtonMiddle,
        ButtonRight
    };

    enum Key
    {

    };

    class Event : public Object
    {
    private:
        Event(GraphicContext *ctx, EventType type);

    public:
        EventType getType() const;
        int getWidth() const;
        int getHeight() const;
        int getMouseX() const;
        int getMouseY() const;
        int getMouseButton() const;
        int getMouseDelta() const;
        GraphicContext *getContext() const;

    public:
        static Event* CreateMousePressEvent(GraphicContext *ctx, MouseButton button, int x, int y);
        static Event* CreateMouseMoveEvent(GraphicContext *ctx, int x, int y);
        static Event* CreateMouseReleaseEvent(GraphicContext *ctx, MouseButton button, int x, int y);
        static Event* CreateMouseWheelEvent(GraphicContext *ctx, int delta);
        static Event* CreateResizeEvent(GraphicContext *ctx, int w, int h);

    private:
        struct Data;
        Data *const d;
    };
}