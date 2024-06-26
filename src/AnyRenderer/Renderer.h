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
        VI_OBJECT_META;
    public:
        enum RenderOrder{
            
        };

    public:
        Renderer();
        virtual ~Renderer();

    public:
        void render();
        void addModel(Model *model);
        Camera *getCamera() const;
        void setCamera(Camera* cam);
        GraphicContext *getContext() const;
        void setContext(GraphicContext *ctx);
        CameraManipulator* getCameraManipulator() const;
        void setCameraManipulator(CameraManipulator* cm);

    private:
        VI_OBJECT_DATA;
    };

} // namespace AnyRenderer
