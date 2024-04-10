#include "Camera.h"

namespace AnyRenderer
{
    Camera::Camera()
    {
        m_mat = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }

    void Camera::set(const glm::vec3 &posi, const glm::vec3 &target, const glm::vec3 &up)
    {
        m_mat = glm::lookAt(posi, target, up);
    }

    void Camera::get(glm::vec3 &o_posi, glm::vec3 &o_target, glm::vec3 &o_up)
    {
        o_posi = -glm::vec3(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
        o_up = glm::vec3(m_mat[0][1], m_mat[1][1], m_mat[2][1]);
        glm::vec3 dir = -glm::vec3(m_mat[0][2], m_mat[1][2], m_mat[2][2]);
        o_target = o_posi + dir;
    }

    void Camera::transform(const glm::mat4x4 &mat)
    {
        m_mat = m_mat * mat;
    }

    void Camera::setMatrix(const glm::mat4x4 &mat)
    {
        m_mat = mat;
    }

    glm::mat4x4 Camera::getMatrix() const
    {
        return m_mat;
    }
}