#pragma once
namespace AnyRenderer
{
    class Renderer;
    class Viewer
    {
    public:
        Viewer();

    public:
        void frame();
        void addRenderer(Renderer *renderer);

    private:
        struct Data;
        Data *const d;
    };
}