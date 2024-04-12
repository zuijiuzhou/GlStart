
#include "anyrenderer_global.h"
#include "Texture.h"

namespace AnyRenderer
{
    Texture::~Texture()
    {
        auto id = getId();
        if (id)
        {
            glDeleteTextures(1, &id);
        }
    }

    void Texture::onBind()
    {
        auto type = getType();
        if (!isCreated())
            create();
        if (!isCreated())
            return;
        if (isDirty())
            update();
        glBindTexture(type, getId());
    }

    void Texture::onUnbind()
    {
        auto type = getType();
        glBindTexture(type, 0);
    }
}