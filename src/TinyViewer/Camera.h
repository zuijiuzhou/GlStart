#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace TinyViewer
{
    class Camera
    {
    private:
        glm::mat4x4 m_mat;

    public:
        Camera();

    public:
        void set(const glm::vec3 &posi, const glm::vec3 &target, const glm::vec3 &up);
        void get(glm::vec3 &o_posi, glm::vec3 &o_target, glm::vec3 &o_up);
        void transform(const glm::mat4x4 &mat);
        glm::mat4x4 getMatrix() const;
    };
}