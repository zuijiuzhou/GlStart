#pragma once
#include "Shape.h"

namespace AnyRenderer
{
    class CubeMap;
    class SkyBox : Shape
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