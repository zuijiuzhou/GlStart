#pragma once
#include "BufferData.h"

namespace AnyRenderer
{
    class Texture : public BufferData
    {
        VI_OBJECT_META;

    public:
        enum Type
        {
            TEXTURE_1D = GL_TEXTURE_1D,
            TEXTURE_2D = GL_TEXTURE_2D,
            TEXTURE_3D = GL_TEXTURE_3D,
            TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP
        };

    public:
        virtual ~Texture();

    public:
        virtual Type getType() const = 0;

    protected:
        virtual void onBind(State& state) override;
        virtual void onUnbind(State& state) override;
        virtual void onRelease(State& state) override;
    };
}