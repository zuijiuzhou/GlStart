#pragma once
#include "anyrenderer_global.h"
#include "Camera.h"

namespace AnyRenderer
{
    class CameraManipulator
    {
    public:
        CameraManipulator(Camera *cameraPtr, GLFWwindow *wndPtr);

    private:
        void init();

        void mouse_button_callback(GLFWwindow *wnd, int button, int action, int mods);
        void cursor_position_callback(GLFWwindow *wnd, double x, double y);
        void scroll_callback(GLFWwindow *wnd, double x, double y);

    private:
        Camera *camera_;
        GLFWwindow *wnd_;

        bool is_rotation_started_ = false;
        bool is_pan_started_ = false;
        bool is_cursor_move_started_ = false;

        glm::vec2 prev_cursor_pt_;
    };

} // namespace AnyRenderer
