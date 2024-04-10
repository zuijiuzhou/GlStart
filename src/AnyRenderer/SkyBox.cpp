#include "SkyBox.h"
#include "CubeMap.h"

namespace AnyRenderer
{

    SkyBox::SkyBox()
    {

    }
    SkyBox::~SkyBox()
    {

    }

    void SkyBox::setCubeMap(CubeMap* tex){
        tex_ = tex;
    }

    void SkyBox::draw(const RenderContext& ctx){
        
    }
}