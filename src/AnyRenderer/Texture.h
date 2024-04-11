#pragma once
#include "anyrenderer_global.h"
namespace AnyRenderer
{
    class Texture
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
        void bind();
        void unbind();
        unsigned int getId() const;
        virtual Type getType() const = 0;

        bool isCreated() const;
        bool isDirty() const;

        void dirty();

    protected:
        virtual void create() = 0;
        virtual void update() = 0;

    protected:
        unsigned int id_ = 0;
        bool is_dirty_ = false;
    };
}