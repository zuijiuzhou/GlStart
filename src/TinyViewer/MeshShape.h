#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>

namespace TinyViewer
{
    class Shader;
    class MeshShape final : public Shape
    {
    public:
        MeshShape();
        virtual ~MeshShape();

    public:
        void draw() override;
        void setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals);
        void setColor(const glm::vec4& color);
        glm::vec4 getColor() const;
    private:
        GLuint vao_ = 0;
        GLuint vbos_[2] = {0, 0};
        std::vector<glm::vec3> vertices_;
        std::vector<glm::vec3> normals_;
        glm::vec4 color_;
    };
}
