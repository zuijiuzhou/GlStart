#include "Renderer.h"
#include <iostream>
#include <functional>
#include <stb_image.h>
#include "Shape.h"
#include "MeshShape.h"
#include "PointCloud.h"
#include "Shader.h"

using namespace TinyViewer;

Renderer::Renderer()
{
    init();
}

Renderer::~Renderer()
{
    for (auto s : shapes_)
    {
        delete s;
    }
}

void Renderer::init()
{
    if (!glfwInit())
    {
        throw std::exception("GLFW init failed");
    }

#ifndef __GL_FIXED_PIPELINE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    auto wnd = glfwCreateWindow(800, 600, "TinyViewer", NULL, NULL);
    glfwMakeContextCurrent(wnd);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(wnd);
        glfwTerminate();
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::exception("GLAD init failed");
    }

    glViewport(0, 0, 800, 600);
    glClearColor(bg_.x, bg_.y, bg_.z, 1.0f);
    glClearDepth(1);
    glClearStencil(1);
    using GLFWFrameBufferSizeCallback = std::function<void(GLFWwindow *, int, int)>;
    using GLFWKeyCallback = std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
    static GLFWFrameBufferSizeCallback framebuffer_size_callback;
    static GLFWKeyCallback key_callback;

    framebuffer_size_callback = [this](GLFWwindow *wnd, int w, int h){ this->framebuffer_size_callback(wnd, w, h); };
    key_callback = [this](GLFWwindow *wnd, int key, int scancode, int action, int mods){ this->key_callback(wnd, key, scancode, action, mods); };
    glfwSetFramebufferSizeCallback(wnd, [](GLFWwindow *wnd, int w, int h){
        static auto callback = framebuffer_size_callback;
        callback(wnd, w, h);
    });
    glfwSetKeyCallback(wnd, [](GLFWwindow *wnd, int key, int scancode, int action, int mods){
        static auto callback = key_callback;
        callback(wnd, key, scancode, action, mods);
    });

    auto camera = new Camera();
    auto cm = new CameraManipulator(camera, wnd);
    auto mesh_shape_shader = Shader::create("res/mesh_shape.vs.glsl", nullptr, "res/mesh_shape.fs.glsl");
    auto point_cloud_shader = Shader::create("res/point_cloud.vs.glsl", nullptr, "res/point_cloud.fs.glsl");

    proj_matrix_ = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 1000.f);
    camera_ = camera;
    cm_ = cm;
    wnd_ = wnd;
    shader_mesh_shape_ = mesh_shape_shader;
    shader_point_cloud_ = point_cloud_shader;
    is_initialized = true;
}

void Renderer::error_callback(int error, const char *desc)
{
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
    if( w == 0 || h == 0)
        return;
    glfwMakeContextCurrent(wnd);
    glViewport(0, 0, w, h);
    proj_matrix_ = glm::perspective(glm::radians(45.f), (float)w / (float)h, 0.1f, 1000.f);
}

void Renderer::run()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(wnd_))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        auto mvp = proj_matrix_ * camera_->getMatrix();
        for (auto shape : shapes_)
        {
            auto mesh_shape = dynamic_cast<MeshShape*>(shape);
            if (mesh_shape)
            {
                shader_mesh_shape_->use();
                shader_mesh_shape_->set("mvp", mvp);
                shader_mesh_shape_->set("rgba", mesh_shape->getColor());
                shape->draw();
                shader_mesh_shape_->unuse();
                continue;
            }
            auto point_cloud = dynamic_cast<PointCloud*>(shape);
            if(shape){
                shader_point_cloud_->use();
                shader_point_cloud_->set("mvp", mvp);
                shape->draw();
                shader_point_cloud_->unuse();
                continue;
            }
        }

        glfwPollEvents();
        glfwSwapBuffers(wnd_);
    }
    glfwTerminate();
}

void Renderer::addShape(Shape *shape)
{
    if (std::find(shapes_.begin(), shapes_.end(), shape) == shapes_.end())
    {
        shapes_.push_back(shape);
    }
}

void Renderer::setBackgroundColor(const glm::vec3& color){
    bg_ = color;
    if(is_initialized)
        glClearColor(bg_.x, bg_.y, bg_.z, 1.0);
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