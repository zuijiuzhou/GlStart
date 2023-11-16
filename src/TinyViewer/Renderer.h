#pragma once

#include "tinyviewer_global.h"
#include <vector>
#include "CameraManipulator.h"

namespace TinyViewer
{
    class Shape;
    class Renderer
    {
    private:
        Camera *m_cameraPtr;
        CameraManipulator *m_cmPtr;
        GLFWwindow *m_wndPtr;
        std::vector<Shape*> m_shapes;

    private:
        void init();

        static void error_callback(int error, const char *desc);
        static void key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
        static void framebuffer_size_callback(GLFWwindow *wnd, int w, int h);

    public:
        Renderer();
        virtual ~Renderer();
        
    public:

        void run();

        void addShape(Shape* shape);
    };

} // namespace TinyViewer
