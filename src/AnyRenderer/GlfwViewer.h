#pragma once
#include <glad/glad.h>

struct GLFWwindow;
namespace AnyRenderer
{
    class Renderer;
    class GlfwViewer
    {
    public:
        GlfwViewer();
        virtual ~GlfwViewer();

    public:
        Renderer *getRenderer() const;

        void run();
        
    private:
        void error_callback(int error, const char *desc);
        void key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow *wnd, int w, int h);
        void mouse_button_callback(GLFWwindow *wnd, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow *wnd, double x, double y);
        void scroll_callback(GLFWwindow *wnd, double x, double y);

    private:
        struct Data;
        Data *const d;
    };
};