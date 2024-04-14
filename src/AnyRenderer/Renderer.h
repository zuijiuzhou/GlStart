#pragma once

#include "anyrenderer_global.h"
#include <vector>

namespace AnyRenderer
{
    class Shader;
    class Drawable;
    class Camera;
    class CameraManipulator;
    class Renderer
    {

    public:
        Renderer();
        virtual ~Renderer();
        
    public:
        void run();
        void addDrawable(Drawable* drawable);
        Camera* getCamera() const;

        // int registerShader(Shader* shader);
    private:
        void init();

        void error_callback(int error, const char *desc);
        void key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow *wnd, int w, int h);

    private:
        Camera *camera_ = nullptr;
        CameraManipulator *cm_ = nullptr;
        GLFWwindow *wnd_ = nullptr;
        std::vector<Drawable*> drawables_;
        std::vector<Shader*> shaders_;
        bool is_initialized = false;

    };

} // namespace AnyRenderer
