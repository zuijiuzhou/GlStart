#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>

namespace TinyViewer
{
    class Shader;
    class MeshShape : public Shape
    {
    public:
        MeshShape();
        virtual ~MeshShape();

    public:
        void draw() override;
        void setData(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors);

    private:
        GLuint m_vao_id = 0;
        GLuint m_vbo_id = 0;
        std::vector<glm::vec3> m_vertices;
        std::vector<glm::vec3> m_colors;
        static Shader* s_shader;
    };
}
