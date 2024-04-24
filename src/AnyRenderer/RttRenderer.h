#pragma once
#include <glad/glad.h>
#include "Renderer.h"

namespace AnyRenderer
{
    class Renderer;
    class Texture;
    class RttRenderer : public Renderer
    {
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
        struct Data;
        Data *const d;
    };
};