#include "Renderer.h"
#include <iostream>
#include <functional>
#include <stb_image.h>
#include "Shape.h"

using namespace TinyViewer;

Renderer::Renderer()
{
    init();
}

Renderer::~Renderer()
{
    for (auto s : m_shapes)
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1);
    glClearStencil(1);

    glfwSetFramebufferSizeCallback(wnd, framebuffer_size_callback);
    glfwSetKeyCallback(wnd, key_callback);

    auto cameraPtr = new Camera();
    auto cmPtr = new CameraManipulator(cameraPtr, wnd);

    m_cameraPtr = cameraPtr;
    m_cmPtr = cmPtr;
    m_wndPtr = wnd;
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
    glfwMakeContextCurrent(wnd);
    glViewport(0, 0, w, h);
}

void Renderer::run()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(m_wndPtr))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        for (auto shape : m_shapes)
        {
            shape->draw();
        }

        glfwPollEvents();
        glfwSwapBuffers(m_wndPtr);
    }
    glfwTerminate();
}

void Renderer::addShape(Shape *shape)
{
    if (std::find(m_shapes.begin(), m_shapes.end(), shape) == m_shapes.end())
    {
        m_shapes.push_back(shape);
    }
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