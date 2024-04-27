#pragma once
#include <glad/glad.h>

namespace AnyRenderer
{
    class Renderer;

    class SdlViewer
    {
    public:
        SdlViewer();
        virtual ~SdlViewer();

    public:
        Renderer *getRenderer() const;

        void initialize();

        bool isInitialized() const;

        void run();
        
    private:
        struct Data;
        Data *const d;
    };
};