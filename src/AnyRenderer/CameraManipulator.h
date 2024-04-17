#pragma once
#include "UIEvent.h"
#include "Object.h"

namespace AnyRenderer
{
    class Camera;
    class CameraManipulator : public Object
    {
    public:
        virtual void notifyMousePressed(MouseButton btn, int x, int y) = 0;
        virtual void notifyMouseReleased(MouseButton btn, int x, int y) = 0;
        virtual void notifyMouseMoved(int x, int y) = 0;
        virtual void notifyMouseScrolled(int delta) = 0;
    protected:
        virtual glm::mat4 computeViewMatrix() const = 0;
        virtual glm::mat4 computeProjectionMatrix() const = 0;
    };

    class StandardCameraManipulator : public CameraManipulator
    {
    public:
    public:
        StandardCameraManipulator(Camera *cam);
        virtual ~StandardCameraManipulator();

    public:
        virtual void notifyMousePressed(MouseButton btn, int x, int y) override;
        virtual void notifyMouseReleased(MouseButton btn, int x, int y) override;
        virtual void notifyMouseMoved(int x, int y) override;
        virtual void notifyMouseScrolled(int delta) override;

    protected:
        virtual glm::mat4 computeViewMatrix() const override;
        virtual glm::mat4 computeProjectionMatrix() const override;

    private:
       struct Data;
       Data* const d;
    };

} // namespace AnyRenderer
