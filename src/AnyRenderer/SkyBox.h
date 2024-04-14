#pragma once
#include "Geometry.h"

namespace AnyRenderer
{
    class CubeMap;
    class SkyBox : public Geometry
    {
    public:
        SkyBox();
        virtual ~SkyBox();

    public:
        void setCubeMap(CubeMap* tex);

        void draw(const RenderContext& ctx) override;

    private:
        CubeMap* tex_ = nullptr;
    };
}