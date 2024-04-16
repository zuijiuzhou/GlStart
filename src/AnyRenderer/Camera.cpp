#include "Camera.h"
#include "anyrenderer_global.h"

namespace AnyRenderer
{
    Camera::Camera()
    {
        view_matrix_ = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }

    void Camera::setClearColor(const glm::vec4 &color)
    {
        clear_color_ = color;
    }

    void Camera::setClearMask(glm::uint32 mask)
    {
        clear_mask_ = mask;
    }

    glm::vec4 Camera::getClearColor() const
    {
        return clear_color_;
    }

    glm::uint32 Camera::getClearMask() const
    {
        return clear_mask_;
    }

    void Camera::setViewMatrixAsLookAt(const glm::vec3 &posi, const glm::vec3 &target, const glm::vec3 &up)
    {
        view_matrix_ = glm::lookAt(posi, target, up);
    }

    void Camera::getViewMatrixAsLookAt(glm::vec3 &o_posi, glm::vec3 &o_target, glm::vec3 &o_up)
    {
        auto &m = view_matrix_;
        o_posi = -glm::vec3(m[3][0], m[3][1], m[3][2]);
        o_up = glm::vec3(m[0][1], m[1][1], m[2][1]);
        auto dir = -glm::vec3(m[0][2], m[1][2], m[2][2]);
        o_target = o_posi + dir;
    }

    void Camera::setViewMatrix(const glm::mat4x4 &mat)
    {
        view_matrix_ = mat;
    }

    glm::vec3 Camera::getViewDir() const
    {
        return -glm::vec3(view_matrix_[0][2], view_matrix_[1][2], view_matrix_[2][2]);
    }

    glm::vec3 Camera::getViewPos() const
    {
        return -glm::vec3(view_matrix_[3][0], view_matrix_[3][1], view_matrix_[3][2]);
    }

    glm::mat4x4 Camera::getViewMatrix() const
    {
        return view_matrix_;
    }

    void Camera::setProjectionMatrix(const glm::mat4x4 &mat)
    {
        proj_matrix_ = mat;
    }

    glm::mat4x4 Camera::getProjectionMatrix() const
    {
        return proj_matrix_;
    }

    glm::mat4x4 Camera::getViewProjectionMatrix() const
    {
        // glm 矩阵行优先
        return proj_matrix_ * view_matrix_;
    }

    void Camera::apply() const
    {
        glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
        glClear(clear_mask_);
    }
}