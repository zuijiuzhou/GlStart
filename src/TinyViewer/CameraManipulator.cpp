#include "CameraManipulator.h"
#include <functional>

using namespace TinyViewer;

namespace
{

}

CameraManipulator::CameraManipulator(Camera *cameraPtr, GLFWwindow *wndPtr)
    : m_cameraPtr(cameraPtr), m_wndPtr(wndPtr)
{
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
        m_wndPtr, (GLFWmousebuttonfun)[](GLFWwindow * wnd, int button, int action, int mods) { auto callback = mouse_button_callback; callback(wnd, button, action, mods); });
    cursor_pos_callback = [this](GLFWwindow *wnd, double x, double y)
    {
        this->cursor_position_callback(wnd, x, y);
    };
    glfwSetCursorPosCallback(
        m_wndPtr, (GLFWcursorposfun)[](GLFWwindow * wnd, double x, double y) { auto callback = cursor_pos_callback; callback(wnd, x, y); });
    scroll_callback = [this](GLFWwindow *wnd, double x, double y)
    {
        this->scroll_callback(wnd, x, y);
    };
    glfwSetScrollCallback(
        m_wndPtr, (GLFWscrollfun)[](GLFWwindow * wnd, double x, double y) { auto callback = scroll_callback; callback(wnd, x, y); });
}

void CameraManipulator::mouse_button_callback(GLFWwindow *wnd, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
        {
            m_isRotationStarted = true;
        }
        break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
        {
            m_isPanStarted = true;
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
        m_isPanStarted = false;
        m_isRotationStarted = false;
        m_isCusorMoveStarted = false;
    }
}
void CameraManipulator::cursor_position_callback(GLFWwindow *wnd, double x, double y)
{
    auto xx = static_cast<float>(x);
    auto yy = static_cast<float>(y);
    if (m_isCusorMoveStarted)
    {
        auto delta_x = xx - m_prevCursorPt.x;
        auto delta_y = yy - m_prevCursorPt.y;

        if (m_isPanStarted)
        {
            auto m = glm::mat4(1.0f);
            m = glm::translate(m, glm::vec3(delta_x / 500, -delta_y / 500, 0));
            m_cameraPtr->transform(m);
        }
        if (m_isRotationStarted)
        {
            glm::mat4 mx(1.0f);
            glm::mat4 my(1.0f);

            mx = glm::rotate(mx, glm::radians(delta_x), glm::vec3(0.0f, 1.0f, 0.0f));
            my = glm::rotate(my, glm::radians(delta_y), glm::vec3(1.0f, 0.0f, 0.0f));

            m_cameraPtr->transform(mx);
            m_cameraPtr->transform(my);
        }
        m_prevCursorPt.x = xx;
        m_prevCursorPt.y = yy;
    }
    else
    {
        m_isCusorMoveStarted = true;
        m_prevCursorPt.x = xx;
        m_prevCursorPt.y = yy;
    }
}
void CameraManipulator::scroll_callback(GLFWwindow *wnd, double x, double y)
{
}