#pragma once

namespace AnyRenderer
{
    class Renderer;
    class Camera;
    class RenderContext
    {
        friend class Renderer;

    private:
        RenderContext(Camera *cam);

    public:
        Camera *getCamera() const;

    private:
        Camera *cam_ = nullptr;
    };
}