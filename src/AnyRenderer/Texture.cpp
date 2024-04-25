
#include "anyrenderer_global.h"
#include "Texture.h"

namespace AnyRenderer
{
    Texture::~Texture()
    {
    }

    void Texture::onBind(RenderContext& ctx)
    {
        auto type = getType();
        glBindTexture(type, getId(ctx));
    }

    void Texture::onUnbind(RenderContext& ctx)
    {
        auto type = getType();
        glBindTexture(type, 0);
    }

    void Texture::onRelease(RenderContext& ctx){
        auto id = getId(ctx);
        glDeleteTextures(1, &id);
    }
}