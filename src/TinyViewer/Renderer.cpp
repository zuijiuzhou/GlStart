#include "Renderer.h"
#include "ShapePainter.h"
#include <stb_image.h>

using namespace TinyViewer;

Renderer::Renderer()
{
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

    GLFWwindow *wnd = glfwCreateWindow(800, 600, "TinyViewer", NULL, NULL);
    glfwMakeContextCurrent(wnd);
    glewInit();

    glViewport(0, 0, 800, 600);

    static auto callback1 = [this](GLFWwindow *wnd, int w, int h)
    { this->framebuffer_size_callback(wnd, w, h); };
    glfwSetFramebufferSizeCallback(
        m_wndPtr, (GLFWframebuffersizefun)[](GLFWwindow * wnd, int w, int h) { callback1(wnd, w, h); });

    static auto callback2 = [this](GLFWwindow *wnd, int key, int scancode, int action, int mods)
    { this->key_callback(wnd, key, scancode, action, mods); };
    glfwSetKeyCallback(
        m_wndPtr, (GLFWkeyfun)[](GLFWwindow * wnd, int key, int scancode, int action, int mods) { callback2(wnd, key, scancode, action, mods); });

    Camera *cameraPtr = new Camera();
    CameraManipulator *cmPtr = new CameraManipulator(cameraPtr, wnd);

    Shader *shaderPtr = new Shader("res/shaders/vs.glsl", "res/shaders/fs.glsl");

    stbi_set_flip_vertically_on_load(true);
    int w, h, nr_channels;
    glGenTextures(1, &m_texture1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture1);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    std::string jpgs[] = {"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};

    for (int i = 0; i < 6; i++)
    {

        unsigned char *data = stbi_load(("res/imgs/" + jpgs[i]).c_str(), &w, &h, &nr_channels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    glGenTextures(1, &m_texture2);
    glBindTexture(GL_TEXTURE_2D, m_texture2);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *img_data = stbi_load("res/imgs/2.jpg", &w, &h, &nr_channels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);

    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(img_data);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_texture2);

    m_shaderPtr = shaderPtr;
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
    glViewport(0, 0, w, h);
}

void Renderer::Render()
{
    ShapePainter painter;
    painter.init();
    m_shaderPtr->use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while (!glfwWindowShouldClose(m_wndPtr))
    {
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClearDepth(1);
        glClearStencil(1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture1);

        // m_shaderPtr->set("viewMatrix", m_cameraPtr->matrix());
        // m_shaderPtr->set("texSkyCube", m_texture1);

        painter.drawTriangle();

        glfwPollEvents();
        glfwSwapBuffers(m_wndPtr);
    }
    glfwTerminate();
}