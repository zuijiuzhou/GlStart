#pragma once

#include "tinyviewer_global.h"
#include "CameraManipulator.h"

namespace TinyViewer
{
    class Renderer{

        private:
        Camera* m_cameraPtr;
        CameraManipulator* m_cmPtr;
        GLFWwindow* m_wndPtr;
        Shader* m_shaderPtr;

        GLuint m_texture1 = 0;
        GLuint m_texture2 = 0;

        private:
        void init();

        void error_callback(int error, const char* desc);
        void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods);

        void framebuffer_size_callback(GLFWwindow* wnd, int w, int h);

        public:
        Renderer();

        void Render();
    };
    
} // namespace TinyViewer

