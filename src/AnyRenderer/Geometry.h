#pragma once
#include "Drawable.h"
#include <vector>
#include <map>
#include <set>
#include "Arrays.h"
#include "PrimitiveSet.h"

namespace AnyRenderer
{
    class Texture;
    class CubeMap;
    class Geometry : public Drawable
    {
    public:
        Geometry();
        virtual ~Geometry();

    public:
        void draw(const RenderContext &ctx) override;
        void addVertexAttribArray(GLuint loc, Array *data);
        void addTexture(GLuint unit, Texture *tex);
        void addPrimitive(PrimitiveSet* prim);
        virtual Shader *getShader() const override;

    public:
        
        static Geometry *createCube(float size, int vertices_loc, int normals_loc, int tex_coords_loc = -1, int cube_map_coords_loc = -1);

    private:
        GLuint vao_ = 0;
        std::map<GLuint, Array *> vbos_;
        std::map<GLuint, Texture *> textures_;
        std::vector<PrimitiveSet *> primitives_;
    };
}
