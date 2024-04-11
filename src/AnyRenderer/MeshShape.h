#pragma once
#include "Shape.h"
#include <vector>
#include <glm/glm.hpp>

namespace AnyRenderer
{
    class Texture;
    class CubeMap;
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
        /**
         * @brief 设置纹理坐标
         * @param coords 当纹理类型为二维纹理时，将忽略Z值
         */
        void setTexCoords(std::vector<glm::vec3> coords);
        void setColors(std::vector<glm::vec4> colors);
        /**
         * @brief 设置纹理贴图
         * @param tex 目前仅支持二维纹理
         * @param unit 绑定的纹理单元
         */
        void setTexture(Texture *tex, unsigned int unit);
        void setEnvMap(CubeMap *tex, unsigned int unit);
        void setDrawType(DrawMode type);

        virtual Shader *getShader() const override;

    public:
        static MeshShape *createCube(float size, bool gen_tex_coords = true);

    private:
        GLuint vao_ = 0;
        GLuint vbos_[5] = {0, 0, 0, 0, 0};

        std::vector<glm::vec3> vertices_;
        std::vector<glm::vec3> normals_;
        std::vector<glm::vec4> colors_;
        std::vector<glm::u32> indices_;
        std::vector<glm::vec3> tex_coords_;
        std::vector<glm::vec3> envmap_coords_;

        Texture *tex_ = nullptr;
        CubeMap *envmap_ = nullptr;
        int tex_unit_ = 0;
        int envmap_unit_ = 1;

        DrawMode draw_mode_ = LineStrip;
    };
}
