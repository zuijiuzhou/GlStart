#include "Camera.h"

using namespace TinyViewer;

Camera::Camera(){
    m_mat = glm::mat4x4(1);
}

 void Camera::set(const glm::vec3& posi, const glm::vec3& target, const glm::vec3& up)
 {
    m_mat = glm::lookAt(posi, target, up);
 }

void Camera::get(glm::vec3& o_posi, glm::vec3& o_target, glm::vec3& o_up)
{
    
}

void Camera::transform(const glm::mat4x4& mat)
{
    m_mat = mat * m_mat;
}

glm::mat4x4 Camera::matrix() const
{
    return m_mat;
}
