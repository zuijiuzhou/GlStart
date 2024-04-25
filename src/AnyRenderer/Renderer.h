#pragma once
#include <vector>
#include "BoundingBox.h"
#include "Object.h"

namespace AnyRenderer
{
    class Shader;
    class Model;
    class Camera;
    class CameraManipulator;
    class RenderContext;
    class Renderer : public Object
    {
    public:
        Renderer();
        virtual ~Renderer();

    public:
        void frame();
        void addModel(Model *model);
        Camera *getCamera() const;
        void setContext(RenderContext* ctx);
        void initialize();
        bool isInitialized() const;
    private:
        struct Data;
        Data *const d;
    };

} // namespace AnyRenderer
