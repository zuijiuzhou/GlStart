#pragma once
#include <glm/mat4x4.hpp>
#include "UIEvent.h"
#include "Object.h"

namespace AnyRenderer
{
    class Camera;
    class CameraManipulator : public Object
    {
    public:
        enum ProjectionType
        {
            Perspective,
            Orthographic
        };

        enum ViewMode{
            Top,
            Bottom,
            Left,
            Right,
            Front,
            Back
        };

    public:
        virtual void notifyMousePressed(MouseButton btn, int x, int y) = 0;
        virtual void notifyMouseReleased(MouseButton btn, int x, int y) = 0;
        virtual void notifyMouseMoved(int x, int y) = 0;
        virtual void notifyMouseScrolled(int delta) = 0;
        virtual void notifyResized(int w, int h) = 0;

        virtual ProjectionType getProjectionType() const = 0;
        virtual void setProjectionType(ProjectionType type) = 0;

        virtual double getFov() const = 0;
        virtual void setFov(double fov) = 0;
        
        virtual void getViewAsLookAt(glm::vec3& eye, glm::vec3& target, glm::vec3& up) = 0;
        virtual void setViewAsLookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) = 0;

        virtual void setViewMode(ViewMode mode) = 0;
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
        virtual void notifyResized(int w, int h) override;

        virtual ProjectionType getProjectionType() const override;
        virtual void setProjectionType(ProjectionType type) override;

        virtual double getFov() const override;
        virtual void setFov(double fov) override;
        
        virtual void getViewAsLookAt(glm::vec3& eye, glm::vec3& target, glm::vec3& up) override;
        virtual void setViewAsLookAt(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up) override;

        virtual void setViewMode(ViewMode mode) override;

    private:
        virtual glm::mat4 computeViewMatrix() const;
        virtual glm::mat4 computeProjectionMatrix() const;

    private:
        struct Data;
        Data *const d;
    };

} // namespace AnyRenderer
