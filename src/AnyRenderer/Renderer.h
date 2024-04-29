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
    class GraphicContext;
    class Renderer : public Object
    {
    public:
        Renderer();
        virtual ~Renderer();

    public:
        void frame();
        void addModel(Model *model);
        void setCamera(Camera* cam);
        Camera *getCamera() const;
        void setContext(GraphicContext *ctx);
        GraphicContext *getContext() const;

    private:
        struct Data;
        Data *const d;
    };

} // namespace AnyRenderer
