#include "RttRenderer.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "Texture2D.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct RttRenderer::Data
    {
        GLFWwindow* wnd = nullptr;
        GLuint fbo_ = 0;
        RefPtr<Texture2D> color_buffer_;
    };

    RttRenderer::RttRenderer() : d(new Data())
    {
        if (!glfwInit())
        {
            throw std::exception("GLFW init failed");
        }

        auto w = 1, h = 1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        auto wnd = glfwCreateWindow(800, 600, "RttRenderer", NULL, NULL);
        glfwMakeContextCurrent(wnd);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(wnd);
            glfwTerminate();
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw std::exception("GLAD init failed");
        }
        d->wnd = wnd;
    }

    RttRenderer::~RttRenderer()
    {

    }

}