#include "CameraManipulator.h"

using namespace TinyViewer;

CameraManipulator::CameraManipulator(Camera *cameraPtr, GLFWwindow *wndPtr)
    : m_cameraPtr(cameraPtr), m_wndPtr(wndPtr)
{
}

void CameraManipulator::init()
{
    static auto callback3 = [this](GLFWwindow *wnd, int button, int action, int mods)
    {
        this->mouse_button_callback(wnd, button, action, mods);
    };
    glfwSetMouseButtonCallback(
        m_wndPtr, (GLFWmousebuttonfun)[](GLFWwindow * wnd, int button, int action, int mods) { callback3(wnd, button, action, mods); });

    static auto callback4 = [this](GLFWwindow *wnd, double x, double y)
    {
        this->cursor_position_callback(wnd, x, y);
    };
    glfwSetCursorPosCallback(
        m_wndPtr, (GLFWcursorposfun)[](GLFWwindow * wnd, double x, double y) { callback4(wnd, x, y); });

    static auto callback5 = [this](GLFWwindow *wnd, double x, double y)
    {
        this->scroll_callback(wnd, x, y);
    };
    glfwSetScrollCallback(
        m_wndPtr, (GLFWscrollfun)[](GLFWwindow * wnd, double x, double y) { callback5(wnd, x, y); });
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
    else if(action == GLFW_RELEASE){
        m_isPanStarted = false;
        m_isRotationStarted = false;
        m_isCusorMoveStarted =false;
    }
}
void CameraManipulator::cursor_position_callback(GLFWwindow *wnd, double x, double y)
{
    if(m_isCusorMoveStarted){
        float deltaX = x- m_prevCursorPt.x;
        float deltaY = y = m_prevCursorPt.y;

        if(m_isPanStarted){
            glm::mat4 matOffset = glm::mat4(1.0f);
            matOffset = glm::translate(matOffset, glm::vec3(deltaX/500, -deltaY/500, 0));
            m_cameraPtr->transform(matOffset);
        }
        if(m_isRotationStarted){
            glm::mat4 matXRotate(1.0f);
            glm::mat4 matYRotate(1.0f);

            matXRotate = glm::rotate(matXRotate, glm::radians(deltaX), glm::vec3(0.0f, 1.0f, 0.0f));
            matYRotate = glm::rotate(matYRotate, glm::radians(deltaY), glm::vec3(1.0f, 0.0f, 0.0f));

            m_cameraPtr->transform(matXRotate);
            m_cameraPtr->transform(matYRotate);
        }
        m_prevCursorPt.x =x;
        m_prevCursorPt.y =y;
    }
    else
    {
        m_isCusorMoveStarted=true;
        m_prevCursorPt.x =x;
        m_prevCursorPt.y =y;
    }
}
void CameraManipulator::scroll_callback(GLFWwindow *wnd, double x, double y)
{
    
}