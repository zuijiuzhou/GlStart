#include "CameraManipulator.h"
#include <functional>

namespace AnyRenderer
{
    CameraManipulator::CameraManipulator(Camera *cameraPtr, GLFWwindow *wndPtr)
        : camera_(cameraPtr), wnd_(wndPtr)
    {
        init();
    }

    void CameraManipulator::init()
    {
        using GLFWMouseButtonCallback = std::function<void(GLFWwindow *, int, int, int)>;
        using GLFWCursorPosCallback = std::function<void(GLFWwindow *, double, double)>;
        using GLFWScrollCallback = std::function<void(GLFWwindow *, double, double)>;
        static GLFWMouseButtonCallback mouse_button_callback;
        static GLFWCursorPosCallback cursor_pos_callback;
        static GLFWScrollCallback scroll_callback;

        mouse_button_callback = [this](GLFWwindow *wnd, int button, int action, int mods)
        {
            this->mouse_button_callback(wnd, button, action, mods);
        };
        glfwSetMouseButtonCallback(
            wnd_, (GLFWmousebuttonfun)[](GLFWwindow * wnd, int button, int action, int mods) { auto callback = mouse_button_callback; callback(wnd, button, action, mods); });
        cursor_pos_callback = [this](GLFWwindow *wnd, double x, double y)
        {
            this->cursor_position_callback(wnd, x, y);
        };
        glfwSetCursorPosCallback(
            wnd_, (GLFWcursorposfun)[](GLFWwindow * wnd, double x, double y) { auto callback = cursor_pos_callback; callback(wnd, x, y); });
        scroll_callback = [this](GLFWwindow *wnd, double x, double y)
        {
            this->scroll_callback(wnd, x, y);
        };
        glfwSetScrollCallback(
            wnd_, (GLFWscrollfun)[](GLFWwindow * wnd, double x, double y) { auto callback = scroll_callback; callback(wnd, x, y); });
    }

    void CameraManipulator::mouse_button_callback(GLFWwindow *wnd, int button, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (button)
            {
            case GLFW_MOUSE_BUTTON_LEFT:
            {
                is_rotation_started_ = true;
            }
            break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
            {
                is_pan_started_ = true;
            }
            break;
            case GLFW_MOUSE_BUTTON_RIGHT:
            {
            }
            break;
            default:
                break;
            }
        }
        else if (action == GLFW_RELEASE)
        {
            is_pan_started_ = false;
            is_rotation_started_ = false;
            is_cursor_move_started_ = false;
        }
    }
    void CameraManipulator::cursor_position_callback(GLFWwindow *wnd, double x, double y)
    {
        auto xx = static_cast<float>(x);
        auto yy = static_cast<float>(y);
        if (is_cursor_move_started_)
        {
            auto delta_x = xx - prev_cursor_pt_.x;
            auto delta_y = yy - prev_cursor_pt_.y;

            if (is_pan_started_)
            {
                auto m = glm::mat4(1.0f);
                m = glm::translate(m, glm::vec3(delta_x / 500, -delta_y / 500, 0));
                camera_->setMatrix(m * camera_->getMatrix());
                // camera_->transform(m);
            }
            if (is_rotation_started_)
            {
                glm::mat4 mx(1.0f);
                glm::mat4 my(1.0f);

                mx = glm::rotate(mx, glm::radians(delta_x / 10), glm::vec3(0.0f, 1.0f, 0.0f));
                my = glm::rotate(my, glm::radians(delta_y / 10), glm::vec3(1.0f, 0.0f, 0.0f));

                camera_->transform(mx);
                camera_->transform(my);
            }
            prev_cursor_pt_.x = xx;
            prev_cursor_pt_.y = yy;
        }
        else
        {
            is_cursor_move_started_ = true;
            prev_cursor_pt_.x = xx;
            prev_cursor_pt_.y = yy;
        }
    }
    void CameraManipulator::scroll_callback(GLFWwindow *wnd, double x, double y)
    {
        // printf("\nx:%f, y:%f", x, y);

        auto delta = y;
        glm::vec3 p, t, u;
        camera_->get(p, t, u);
        glm::vec3 dir = t - p;
        dir = dir * static_cast<float>(-y / 10);
        glm::mat4 m(1.0);
        m = glm::translate(m, dir);
        camera_->transform(m);
    }
}