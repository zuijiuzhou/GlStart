#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>

namespace TinyViewer
{
    class PointCloud final : public Shape
    {
    public:
        PointCloud();
        virtual ~PointCloud();

    public:
        void draw() override;
        void setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors);
    private:
        GLuint vao_ = 0;
        GLuint vbos_[2] = {0, 0};
        std::vector<glm::vec3> vertices_;
        std::vector<glm::vec3> colors_;
    };
}
