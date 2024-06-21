#pragma once
#include <glad/glad.h>
#include "Renderer.h"

namespace AnyRenderer
{
    class Renderer;
    class Texture;
    class RttRenderer : public Renderer
    {
        VI_OBJECT_META;

    public:
        RttRenderer();
        virtual ~RttRenderer();

    public:
        void resize(int w, int h);

        GLsizei getWidth() const;

        GLsizei getHeight() const;

        Texture* getColorBuffer() const;

        void initialize();

        bool isInitialized() const;

    private:
        VI_OBJECT_DATA;
    };
};