#pragma once
#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>

namespace AnyRenderer
{
    class PointCloud final : public Shape
    {
    public:
        PointCloud();
        virtual ~PointCloud();

    public:
        void draw(const RenderContext &ctx) override;
        void setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors);
        virtual Shader *getShader() const override;

    private:
        GLuint vao_ = 0;
        GLuint vbos_[2] = {0, 0};
        std::vector<glm::vec3> vertices_;
        std::vector<glm::vec3> colors_;
    };
}
