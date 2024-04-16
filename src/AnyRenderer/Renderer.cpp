#include "Renderer.h"
#include <iostream>
#include <functional>
#include <stb_image.h>
#include "Utilities/Resources.h"
#include "Group.h"
#include "Drawable.h"
#include "Shader.h"
#include "StateSet.h"
#include "RenderContext.h"
#include "CameraManipulator.h"

namespace AnyRenderer
{
    Renderer::Renderer()
    {
        init();
    }

    Renderer::~Renderer()
    {
        for (auto m : models_)
        {
            m->unref();
        }
    }

    void Renderer::init()
    {
        if (!glfwInit())
        {
            throw std::exception("GLFW init failed");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        auto wnd = glfwCreateWindow(800, 600, "AnyRenderer", NULL, NULL);
        glfwMakeContextCurrent(wnd);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(wnd);
            glfwTerminate();
            std::cout << "Failed to initialize GLAD" << std::endl;
            throw std::exception("GLAD init failed");
        }

        glViewport(0, 0, 800, 600);
        glClearDepth(1);
        glClearStencil(1);
        using GLFWFrameBufferSizeCallback = std::function<void(GLFWwindow *, int, int)>;
        using GLFWKeyCallback = std::function<void(GLFWwindow * window, int key, int scancode, int action, int mods)>;
        static GLFWFrameBufferSizeCallback framebuffer_size_callback;
        static GLFWKeyCallback key_callback;

        framebuffer_size_callback = [this](GLFWwindow *wnd, int w, int h)
        { this->framebuffer_size_callback(wnd, w, h); };
        key_callback = [this](GLFWwindow *wnd, int key, int scancode, int action, int mods)
        { this->key_callback(wnd, key, scancode, action, mods); };
        glfwSetFramebufferSizeCallback(wnd, [](GLFWwindow *wnd, int w, int h)
                                       {
        static auto callback = framebuffer_size_callback;
        callback(wnd, w, h); });
        glfwSetKeyCallback(wnd, [](GLFWwindow *wnd, int key, int scancode, int action, int mods)
                           {
        static auto callback = key_callback;
        callback(wnd, key, scancode, action, mods); });

        auto camera = new Camera();
        auto cm = new CameraManipulator(camera, wnd);
        camera->setProjectionMatrix(glm::perspective(glm::radians(45.f), 800.f / 600.f, 1.f, 1000.f));
        camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        camera->setClearColor(glm::vec4(0));
        camera_ = camera;
        cm_ = cm;
        wnd_ = wnd;
        is_initialized = true;
    }

    void Renderer::error_callback(int error, const char *desc)
    {

        auto mesh_shape_shader = Shader::create(__RES("shaders/mesh_shape.vs.glsl"), nullptr, __RES("shaders/mesh_shape.fs.glsl"));
        auto point_cloud_shader = Shader::create(__RES("shaders/point_cloud.vs.glsl"), nullptr, __RES("shaders/point_cloud.fs.glsl"));
    }

    void Renderer::key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods)
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

    void Renderer::framebuffer_size_callback(GLFWwindow *wnd, int w, int h)
    {
        if (w == 0 || h == 0)
            return;
        glfwMakeContextCurrent(wnd);
        glViewport(0, 0, w, h);
        camera_->setProjectionMatrix(glm::perspective(glm::radians(45.f), (float)w / (float)h, 0.1f, 1000.f));
    }

    void Renderer::run()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_PROGRAM_POINT_SIZE);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glDepthFunc(GL_LESS);
        RenderContext ctx(camera_);

        BoundingBox bb;
        for (auto model : models_)
        {
            bb.combine(model->getBoundingBox());
        }
        auto def_view_center = bb.getCenter();
        auto def_view_dir = glm::vec3(0., 0., -1.0);
        auto def_view_dist = bb.getRadius();
        if(def_view_dist < 0.01) def_view_dist = 2.;
        auto def_view_pos = def_view_center - def_view_dir * glm::vec3(def_view_dist);
        camera_->setViewMatrixAsLookAt(def_view_pos, def_view_center, glm::vec3(0, 1, 0));
        camera_->setProjectionMatrix(glm::perspective<double>(30, 1, 1.f, def_view_dist * 2));

        while (!glfwWindowShouldClose(wnd_))
        {
            camera_->apply();
            auto matrix_v = camera_->getViewMatrix();
            auto matrix_mv = camera_->getViewProjectionMatrix();
            auto view_dir = camera_->getViewDir();
            for (auto model : models_)
            {
                auto stateset = model->getStateSet();
                if (stateset)
                {
                    stateset->apply(ctx);
                    auto shader = ctx.getCurrentShader();
                    if (shader)
                    {
                        shader->set("matrix_m", glm::mat4(1.0));
                        shader->set("matrix_v", matrix_v);
                        shader->set("matrix_mv", matrix_v);
                        shader->set("matrix_mvp", matrix_mv);
                        shader->set("view_dir", view_dir);
                    }
                }
                for (auto drawable : model->getDrawables())
                {
                    drawable->draw(ctx);
                }
            }

            glfwPollEvents();
            glfwSwapBuffers(wnd_);
        }
        glfwTerminate();
    }

    void Renderer::addModel(Group *model)
    {
        if (std::find(models_.begin(), models_.end(), model) == models_.end())
        {
            models_.push_back(model);
            model->ref();
        }
    }

    Camera *Renderer::getCamera() const
    {
        return camera_;
    }
}