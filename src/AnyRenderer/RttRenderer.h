#pragma once
#include <glad/glad.h>
#include "Renderer.h"

namespace AnyRenderer
{
    class Renderer;
    class CameraManipulator;
    class RttRenderer : public Renderer
    {
    public:
        RttRenderer();
        virtual ~RttRenderer();

    public:
        

    private:
        struct Data;
        Data *const d;
    };
};