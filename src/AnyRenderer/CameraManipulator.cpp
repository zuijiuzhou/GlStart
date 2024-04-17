#include "CameraManipulator.h"
#include <functional>
#include "Camera.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct StandardCameraManipulator::Data
    {
        RefPtr<Camera> camera;

        bool is_rotation_started = false;
        bool is_pan_started = false;
        bool is_cursor_move_started = false;

        glm::vec2 prev_cursor_pt;
    };

    StandardCameraManipulator::StandardCameraManipulator(Camera *cam) : d(new Data())
    {
        d->camera = cam;
    }
    StandardCameraManipulator::~StandardCameraManipulator()
    {
        delete d;
    }
    void StandardCameraManipulator::notifyMouseReleased(MouseButton btn, int x, int y)
    {
        d->is_pan_started = false;
        d->is_rotation_started = false;
        d->is_cursor_move_started = false;
    }

    void StandardCameraManipulator::notifyMousePressed(MouseButton btn, int x, int y)
    {
        switch (btn)
        {
        case MouseButton::ButtonLeft:
        {
            d->is_rotation_started = true;
        }
        break;
        case MouseButton::ButtonMiddle:
        {
            d->is_pan_started = true;
        }
        break;
        case MouseButton::ButtonRight:
        {
        }
        break;
        default:
            break;
        }
    }

    void StandardCameraManipulator::notifyMouseMoved(int x, int y)
    {
        auto xx = static_cast<float>(x);
        auto yy = static_cast<float>(y);
        if (d->is_cursor_move_started)
        {
            auto delta_x = xx - d->prev_cursor_pt.x;
            auto delta_y = yy - d->prev_cursor_pt.y;

            auto vm = d->camera->getViewMatrix();
            if (d->is_pan_started)
            {
                auto m = glm::mat4(1.0f);
                m = glm::translate(m, glm::vec3(delta_x / 500, -delta_y / 500, 0));
                vm = m * vm;
                d->camera->setViewMatrix(vm);
            }
            if (d->is_rotation_started)
            {
                glm::mat4 mx(1.0f);
                glm::mat4 my(1.0f);

                mx = glm::rotate(mx, glm::radians(delta_x / 10), glm::vec3(0.0f, 1.0f, 0.0f));
                my = glm::rotate(my, glm::radians(delta_y / 10), glm::vec3(1.0f, 0.0f, 0.0f));

                
            }
            d->prev_cursor_pt.x = xx;
            d->prev_cursor_pt.y = yy;
        }
        else
        {
            d->is_cursor_move_started = true;
            d->prev_cursor_pt.x = xx;
            d->prev_cursor_pt.y = yy;
        }
    }

    void StandardCameraManipulator::notifyMouseScrolled(int delta)
    {
        auto vm = d->camera->getViewMatrix();
        glm::vec3 p, t, u, dir;
        d->camera->getViewMatrixAsLookAt(p, t, u);
        dir = t - p;
        dir = dir * static_cast<float>(-delta / 10);
        glm::mat4 m(1.0);
        m = glm::translate(m, dir);
        vm *= m;
        d->camera->setViewMatrix(vm);
    }
}