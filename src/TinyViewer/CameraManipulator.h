#ifndef _CAMERAMANIPULATOR_H_
#define _CAMERAMANIPULATOR_H_
#include "tinyviewer_global.h"
#include "Camera.h"

namespace TinyViewer
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
        Camera *m_cameraPtr;
        GLFWwindow *m_wndPtr;

        bool m_isRotationStarted = false;
        bool m_isPanStarted = false;
        bool m_isCusorMoveStarted = false;

        glm::vec2 m_prevCursorPt;
    };

} // namespace TinyViewer

#endif
