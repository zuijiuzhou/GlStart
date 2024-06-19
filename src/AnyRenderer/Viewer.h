#pragma once
#include "Object.h"
namespace AnyRenderer
{
    class Renderer;
    class Viewer : public Object
    {
        VI_OBJECT_META;

    public:
        Viewer();

    public:
        void frame();
        void addRenderer(Renderer *renderer);
        int getNbRenderers() const;
        Renderer* getRendererAt(int idx) const;

    private:
        struct Data;
        Data *const d;
    };
}