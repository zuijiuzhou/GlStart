#pragma once
#include <glad/glad.h>

namespace AnyRenderer
{
    class Viewer;

    class GlfwViewer
    {
    public:
        GlfwViewer();
        virtual ~GlfwViewer();

    public:
        Viewer *getViewer() const;

        void initialize();

        bool isInitialized() const;

        void run();
    
    private:
        struct Data;
        Data *const d;
    };
};