#pragma once

#include "tinyviewer_global.h"
#include <vector>
#include "CameraManipulator.h"

namespace TinyViewer
{
    class Shader;
    class Shape;
    class Renderer
    {
    private:
        Camera *camera_ = nullptr;
        CameraManipulator *cm_ = nullptr;
        GLFWwindow *wnd_ = nullptr;
        std::vector<Shape*> shapes_;
        Shader* shader_mesh_shape_ = nullptr;
        Shader* shader_point_cloud_ = nullptr;
        glm::mat4x4 proj_matrix_;
        glm::vec3 bg_;
        bool is_initialized = false;
    private:
        void init();

        void error_callback(int error, const char *desc);
        void key_callback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
        void framebuffer_size_callback(GLFWwindow *wnd, int w, int h);

    public:
        Renderer();
        virtual ~Renderer();
        
    public:

        void run();

        void addShape(Shape* shape);

        void setBackgroundColor(const glm::vec3& color);
    };

} // namespace TinyViewer
