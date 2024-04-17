#pragma once
#include <vector>
#include "BoundingBox.h"
#include "Object.h"

namespace AnyRenderer
{
    class Shader;
    class Group;
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
        void addModel(Group *model);
        Camera *getCamera() const;
        void initialize();

    private:
        struct Data;
        Data *const d;
    };

} // namespace AnyRenderer
