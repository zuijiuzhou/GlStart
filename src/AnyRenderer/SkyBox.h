#pragma once
#include "Drawable.h"

namespace AnyRenderer
{
    class CubeMap;
    class SkyBox : Drawable
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