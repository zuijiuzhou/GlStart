#include "Renderer.h"
#include <iostream>
#include <functional>
#include <stb_image.h>
#include "Utilities/Resources.h"
#include "Drawable.h"
#include "Shader.h"
#include "RenderContext.h"
#include "CameraManipulator.h"
#include "StateSet.h"

namespace AnyRenderer
{
    Renderer::Renderer()
    {
        init();
    }

    Renderer::~Renderer()
    {
        for (auto d : drawables_)
        {
            delete d;
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
        camera->setProjectionMatrix(glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 1000.f));
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
        while (!glfwWindowShouldClose(wnd_))
        {
            Shader *prev_shader_ = nullptr;
            camera_->apply();
            auto matrix_v = camera_->getViewMatrix();
            auto matrix_mv = camera_->getViewProjectionMatrix();
            auto view_dir = camera_->getViewDir();
            for (auto drawable : drawables_)
            {
                auto shader = drawable->getShader();
                ctx.current_shader_ = shader;
                if (shader != prev_shader_)
                {
                    if (shader)
                    {
                        shader->use();
                        shader->set("matrix_m", glm::mat4(1.0));
                        shader->set("matrix_v", matrix_v);
                        shader->set("matrix_mv", matrix_v);
                        shader->set("matrix_mvp", matrix_mv);
                        shader->set("view_dir", view_dir);
                    }
                }
                auto stateset = drawable->getStateSet();
                if(stateset){
                    stateset->apply(ctx);
                }
                drawable->draw(ctx);
                prev_shader_ = shader;
            }

            glfwPollEvents();
            glfwSwapBuffers(wnd_);
        }
        glfwTerminate();
    }

    void Renderer::addDrawable(Drawable *drawable)
    {
        if (std::find(drawables_.begin(), drawables_.end(), drawable) == drawables_.end())
        {
            drawables_.push_back(drawable);
        }
    }

    Camera *Renderer::getCamera() const
    {
        return camera_;
    }
    // stbi_set_flip_vertically_on_load(true);
    //     int w, h, nr_channels;
    //     glGenTextures(1, &m_texture1);
    //     glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture1);
    //     glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //     glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //     glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //     glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    //     std::string jpgs[] = {"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};

    //     for (int i = 0; i < 6; i++)
    //     {

    //         unsigned char *data = stbi_load(("res/imgs/" + jpgs[i]).c_str(), &w, &h, &nr_channels, 0);
    //         glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //         stbi_image_free(data);
    //     }

    //     glGenerateMipmap(GL_TEXTURE_2D);
    //     glGenTextures(1, &m_texture2);
    //     glBindTexture(GL_TEXTURE_2D, m_texture2);
    //     glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //     glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //     glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //     unsigned char *img_data = stbi_load("res/imgs/2.jpg", &w, &h, &nr_channels, 0);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);

    //     glGenerateMipmap(GL_TEXTURE_2D);
    //     stbi_image_free(img_data);

    //     glActiveTexture(GL_TEXTURE1);
    //     glBindTexture(GL_TEXTURE_2D, m_texture2);
}