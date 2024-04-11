#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace AnyRenderer
{
    class Camera
    {
    public:
        Camera();

    public:
        void setClearColor(const glm::vec4& color);
        void setClearMask(glm::uint32 mask);

        glm::vec4 getClearColor() const;
        glm::uint32 getClearMask() const;

        void getViewMatrixAsLookAt(glm::vec3 &o_posi, glm::vec3 &o_target, glm::vec3 &o_up);
        void setViewMatrixAsLookAt(const glm::vec3 &posi, const glm::vec3 &target, const glm::vec3 &up);
        void setViewMatrix(const glm::mat4x4 &mat);
        void setProjectionMatrix(const glm::mat4x4 &mat);
        glm::mat4x4 getViewMatrix() const;
        glm::mat4x4 getProjectionMatrix() const;
        glm::mat4x4 getViewProjectionMatrix() const;

        void apply() const;

    private:
        glm::mat4x4 view_matrix_;
        glm::mat4x4 proj_matrix_;
        glm::vec4 clear_color_;
        glm::uint32 clear_mask_;
    };
}