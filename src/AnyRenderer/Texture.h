#pragma once
#include "BufferData.h"

namespace AnyRenderer
{
    class Texture : public BufferData
    {
    public:
        enum Type
        {
            Texture1D = GL_TEXTURE_1D,
            Texture2D = GL_TEXTURE_2D,
            Texture3D = GL_TEXTURE_3D,
            TexCubeMap = GL_TEXTURE_CUBE_MAP
        };

    public:
        virtual ~Texture();

    public:
        virtual Type getType() const = 0;

    protected:
        virtual void onBind() override;
        virtual void onUnbind() override;
    };
}