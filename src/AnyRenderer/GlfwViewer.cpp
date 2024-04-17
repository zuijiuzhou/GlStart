#include "GlfwViewer.h"
#include <iostream>
#include <functional>
#include <memory>
#include <glm/glm.hpp>
#include "Renderer.h"
#include "Camera.h"
#include "CameraManipulator.h"
#include "UIEvent.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct GlfwViewer::Data
    {
        RefPtr<Renderer> renderer;
        RefPtr<CameraManipulator> cm;
        GLFWwindow *wnd = nullptr;
        glm::vec2 cursor_pt;
    };

    GlfwViewer::GlfwViewer() : d(new Data())
    {
        if (!glfwInit())
        {
            throw std::exception("GLFW init failed");
        }

        auto w = 800, h = 600;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        auto wnd = glfwCreateWindow(800, 600, "GlfwViewer", NULL, NULL);
        glfwMakeContextCurrent(wnd);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(wnd);
            glfwTerminate();
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw std::exception("GLAD init failed");
        }

        using GLFWFrameBufferSizeCallback = std::function<void(GLFWwindow *, int, int)>;
        using GLFWKeyCallback = std::function<void(GLFWwindow * window, int key, int scancode, int action, int mods)>;
        using GLFWMouseButtonCallback = std::function<void(GLFWwindow *, int, int, int)>;
        using GLFWCursorPosCallback = std::function<void(GLFWwindow *, double, double)>;
        using GLFWScrollCallback = std::function<void(GLFWwindow *, double, double)>;
        static GLFWFrameBufferSizeCallback framebuffer_size_callback;
        static GLFWKeyCallback key_callback;
        static GLFWMouseButtonCallback mouse_button_callback;
        static GLFWCursorPosCallback cursor_pos_callback;
        static GLFWScrollCallback scroll_callback;

        framebuffer_size_callback = [this](GLFWwindow *wnd, int w, int h)
        { this->framebuffer_size_callback(wnd, w, h); };
        key_callback = [this](GLFWwindow *wnd, int key, int scancode, int action, int mods)
        { this->key_callback(wnd, key, scancode, action, mods); };
        mouse_button_callback = [this](GLFWwindow *wnd, int button, int action, int mods)
        { this->mouse_button_callback(wnd, button, action, mods); };
        cursor_pos_callback = [this](GLFWwindow *wnd, double x, double y)
        { this->cursor_position_callback(wnd, x, y); };
        scroll_callback = [this](GLFWwindow *wnd, double x, double y)
        { this->scroll_callback(wnd, x, y); };

        glfwSetFramebufferSizeCallback(
            wnd, (GLFWframebuffersizefun)[](GLFWwindow * wnd, int w, int h) { static auto callback = framebuffer_size_callback; callback(wnd, w, h); });
        glfwSetKeyCallback(
            wnd, (GLFWkeyfun)[](GLFWwindow * wnd, int key, int scancode, int action, int mods) { static auto callback = key_callback; callback(wnd, key, scancode, action, mods); });
        glfwSetMouseButtonCallback(
            wnd, (GLFWmousebuttonfun)[](GLFWwindow * wnd, int button, int action, int mods) { auto callback = mouse_button_callback; callback(wnd, button, action, mods); });
        glfwSetCursorPosCallback(
            wnd, (GLFWcursorposfun)[](GLFWwindow * wnd, double x, double y) { auto callback = cursor_pos_callback; callback(wnd, x, y); });
        glfwSetScrollCallback(
            wnd, (GLFWscrollfun)[](GLFWwindow * wnd, double x, double y) { auto callback = scroll_callback; callback(wnd, x, y); });

        auto renderer = new Renderer();
        renderer->initialize();
        auto cm = new StandardCameraManipulator(renderer->getCamera());

        auto cam = renderer->getCamera();
        cam->setViewport(0., 0., w, h);
        cam->setClearDepth(1.0);
        cam->setClearStencil(1);
        cam->setClearColor(glm::vec4(0., 0., 0., 1.));
        cam->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_PROGRAM_POINT_SIZE);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glDepthFunc(GL_LESS);

        d->renderer = renderer;
        d->cm = cm;
        d->wnd = wnd;
    }

    GlfwViewer::~GlfwViewer()
    {
        if(d->wnd){
            glfwDestroyWindow(d->wnd);
        }
        delete d;
    }

    Renderer *GlfwViewer::getRenderer() const
    {
        return d->renderer.get();
    }

    void GlfwViewer::run(){
        glfwShowWindow(d->wnd);
        glfwMakeContextCurrent(d->wnd);
        while (!glfwWindowShouldClose(d->wnd))
        {
            d->renderer->frame();
            glfwPollEvents();
            glfwSwapBuffers(d->wnd);
        }
    }

    void GlfwViewer::error_callback(int error, const char *desc)
    {
    }

    void GlfwViewer::key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            return;
        }
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
        {
            glfwSetWindowShouldClose(wnd, GL_TRUE);
        }
        break;

        default:
            break;
        }
    }

    void GlfwViewer::framebuffer_size_callback(GLFWwindow *wnd, int w, int h)
    {
        if (w == 0 || h == 0)
            return;
        glfwMakeContextCurrent(wnd);
        d->cm->notifyResized(w, h);
    }

    void GlfwViewer::mouse_button_callback(GLFWwindow *wnd, int button, int action, int mods)
    {
        auto btn = ButtonLeft;
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            btn = ButtonLeft;
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            btn = ButtonLeft;
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            btn = ButtonLeft;
        if (action == GLFW_PRESS)
        {
            d->cm->notifyMousePressed(ButtonLeft, d->cursor_pt.x, d->cursor_pt.y);
        }
        else if (action == GLFW_RELEASE)
        {
            d->cm->notifyMouseReleased(ButtonLeft, d->cursor_pt.x, d->cursor_pt.y);
        }
    }

    void GlfwViewer::cursor_position_callback(GLFWwindow *wnd, double x, double y)
    {
        d->cursor_pt = glm::vec2(x, y);
        d->cm->notifyMouseMoved(x, y);
    }

    void GlfwViewer::scroll_callback(GLFWwindow *wnd, double x, double y)
    {
        d->cm->notifyMouseScrolled(y);
    }

}