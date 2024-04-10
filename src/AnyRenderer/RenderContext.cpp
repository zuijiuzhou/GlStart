#include "RenderContext.h"

namespace AnyRenderer
{
    RenderContext::RenderContext(Camera *cam) : cam_(cam)
    {
    }

    Camera *RenderContext::getCamera() const
    {
        return cam_;
    }
}