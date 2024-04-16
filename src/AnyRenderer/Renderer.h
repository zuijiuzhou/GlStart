#pragma once

#include "anyrenderer_global.h"
#include <vector>

namespace AnyRenderer
{
    class Shader;
    class Group;
    class Camera;
    class CameraManipulator;
    class Renderer
    {

    public:
        Renderer();
        virtual ~Renderer();
        
    public:
        void run();
        void addModel(Group* model);
        Camera* getCamera() const;

    private:
        void init();

        void error_callback(int error, const char *desc);
        void key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow *wnd, int w, int h);

    private:
        Camera *camera_ = nullptr;
        CameraManipulator *cm_ = nullptr;
        GLFWwindow *wnd_ = nullptr;
        std::vector<Group*> models_;
        std::vector<Shader*> shaders_;
        bool is_initialized = false;

    };

} // namespace AnyRenderer
