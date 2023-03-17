#pragma once
#include "tinyviewer_global.h"
#include "Shader.h"

namespace TinyViewer
{
    class ShapePainter
    {
    private:
        bool m_isInitialized = false;

    public:
        void init();
        void uninit();
        void drawTriangle();
    }
}