#pragma once
#include "Geometry.h"
namespace AnyRenderer
{
    class SimpleGeometry : public Geometry
    {
    public:
        SimpleGeometry();
        virtual ~SimpleGeometry();

    public:
        virtual void preDraw(const RenderContext &ctx) override;

        void setVertices(Vec3fArray *vertices);
        void setNormals(Vec3fArray *normals);
        void setColors(Vec4fArray *colors);
    };
}