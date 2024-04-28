
#include "anyrenderer_global.h"
#include "Texture.h"

namespace AnyRenderer
{
    Texture::~Texture()
    {
    }

    void Texture::onBind(State& state)
    {
        auto type = getType();
        glBindTexture(type, getId(state));
    }

    void Texture::onUnbind(State& state)
    {
        auto type = getType();
        glBindTexture(type, 0);
    }

    void Texture::onRelease(State& state){
        auto id = getId(state);
        glDeleteTextures(1, &id);
    }
}