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
        void addPrimitive(PrimitiveSet *prim);

        virtual BoundingBox getBoundingBox() const override;
        void setBoundingBox(const BoundingBox &bb);

    public:
        static Geometry *createCube(float size, int vertices_loc, int normals_loc = -1, int tex_2d_coords_loc = -1, int cube_map_coords_loc = -1);

    private:
        struct Data;
        Data *const d;
    };
}
