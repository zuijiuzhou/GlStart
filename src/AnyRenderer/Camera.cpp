﻿#include "Camera.h"

namespace AnyRenderer
{
    Camera::Camera()
        : clear_depth_(1.0),
          clear_stencil_(1),
          clear_color_(0.f, 0.f, 0.f, 1.f),
          clear_mask_(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT),
          view_pos_(0.f, 0.f, 10.f),
          view_center_(0.f, 0.f, 0.f),
          view_up_(0.f, 1.f, 0.f),
          near_(1.0), far_(1000.0),
          fov_(30.0),
          vp_w_(1.0),
          vp_h_(1.0)
    {
        view_matrix_ = computeViewMatrix();
        proj_matrix_ = computeProjectionMatrix();
    }

    glm::vec4 Camera::getClearColor() const
    {
        return clear_color_;
    }
    void Camera::setClearColor(const glm::vec4 &color)
    {
        clear_color_ = color;
    }

    GLdouble Camera::getClearDepth() const
    {
        return clear_depth_;
    }
    void Camera::setClearDepth(GLdouble depth)
    {
        clear_depth_ = depth;
    }
    GLint Camera::getClearStencil() const
    {
        return clear_stencil_;
    }

    void Camera::setClearStencil(GLint val)
    {
        clear_stencil_ = val;
    }
    GLbitfield Camera::getClearMask() const
    {
        return clear_mask_;
    }

    void Camera::setClearMask(GLbitfield mask)
    {
        clear_mask_ = mask;
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

    void Camera::setViewport(int x, int y, int w, int h)
    {
        vp_x_ = x;
        vp_y_ = y;
        vp_w_ = w;
        vp_h_ = h;
        glViewport(x, y, w, h);
        setProjectionMatrix(computeProjectionMatrix());
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

    glm::mat4 Camera::computeViewMatrix() const
    {
        return glm::lookAt(view_pos_, view_center_, view_up_);
    }

    glm::mat4 Camera::computeProjectionMatrix() const
    {
        return glm::perspective(glm::radians(fov_), vp_w_ / vp_h_, near_, far_);
    }

    void Camera::apply() const
    {
        glClearColor(clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
        glClearDepth(clear_depth_);
        glClearStencil(clear_stencil_);
        glClear(clear_mask_);
    }
}