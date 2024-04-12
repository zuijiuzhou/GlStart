#pragma once
#include "Shape.h"
#include <vector>
#include <map>
#include <set>
#include "Arrays.h"
#include "PrimitiveSet.h"

namespace AnyRenderer
{
    class Texture;
    class CubeMap;
    class MeshShape : public Shape
    {
    public:
        MeshShape();
        virtual ~MeshShape();

    public:
        void draw(const RenderContext &ctx) override;
        void addVertexAttribArray(GLuint loc, Array *data);
        void addTexture(GLuint unit, Texture *tex);
        void addPrimitive(PrimitiveSet* prim);
        virtual Shader *getShader() const override;

    public:
        static MeshShape *createCube(float size, bool gen_tex_coords = true);

    private:
        GLuint vao_ = 0;
        std::map<GLuint, Array *> vbos_;
        std::map<GLuint, Texture *> textures_;
        std::vector<PrimitiveSet *> primitives_;
    };
}
