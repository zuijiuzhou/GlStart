#pragma once
#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>

namespace AnyRenderer
{
    class Texture;
    class MeshShape final : public Shape
    {
    public:
        enum DrawMode
        {
            Lines = GL_LINES,
            LineLoop = GL_LINE_LOOP,
            LineStrip = GL_LINE_STRIP,
            Triangles = GL_TRIANGLES,
            TriangleStrip = GL_TRIANGLE_STRIP,
            TriangleFan = GL_TRIANGLE_FAN,
            Quads = GL_QUADS
        };

    public:
        MeshShape();
        virtual ~MeshShape();

    public:
        void draw(const RenderContext &ctx) override;
        void setVertices(std::vector<glm::vec3> vertices);
        void setNormals(std::vector<glm::vec3> normals);
        void setIndices(std::vector<glm::u32> indices);
        void setTexCoords(std::vector<glm::vec3> coords);
        void setTexCoords(std::vector<glm::vec2> coords);
        void setColors(std::vector<glm::vec4> colors);
        void setTexture(Texture *tex, unsigned int unit);
        void setDrawType(DrawMode type);

        virtual Shader *getShader() const override;

    public:
        static MeshShape *createCube(double size);

    private:
        GLuint vao_ = 0;
        GLuint vbos_[4] = {0, 0, 0, 0};

        std::vector<glm::vec3> vertices_;
        std::vector<glm::vec3> normals_;
        std::vector<glm::vec4> colors_;
        std::vector<glm::u32> indices_;
        std::vector<glm::vec3> tex_coords_3d_;
        std::vector<glm::vec2> tex_coords_2d_;

        Texture *tex_ = nullptr;
        int tex_unit_ = -1;
        DrawMode draw_mode_ = Lines;
    };
}
