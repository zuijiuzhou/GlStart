#pragma once

#include "anyrenderer_global.h"
#include <vector>
#include "CameraManipulator.h"

namespace AnyRenderer
{
    class Shader;
    class Shape;
    class Renderer
    {

    public:
        Renderer();
        virtual ~Renderer();
        
    public:
        void run();

        void addShape(Shape* shape);

    private:
        void init();

        void error_callback(int error, const char *desc);
        void key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow *wnd, int w, int h);

    private:
        Camera *camera_ = nullptr;
        CameraManipulator *cm_ = nullptr;
        GLFWwindow *wnd_ = nullptr;
        std::vector<Shape*> shapes_;
        bool is_initialized = false;
    };

} // namespace AnyRenderer
