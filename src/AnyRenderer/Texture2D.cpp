#include "Texture2D.h"
#include <stb_image.h>
#include "anyrenderer_global.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(Texture2D, Texture);

    struct Texture2D::Data
    {
        std::string img;
        GLsizei w = 0;
        GLsizei h = 0;
        GLint format = 0;
        GLint informat = 0;
    };

    Texture2D::Texture2D() : d(new Data())
    {
    }

    Texture2D::~Texture2D()
    {
        delete d;
    }

    Texture::Type Texture2D::getType() const
    {
        return Type::TEXTURE_2D;
    }

    void Texture2D::setWidth(GLsizei w)
    {
        d->w = w;
        dirty();
    }

    void Texture2D::setHeight(GLsizei h)
    {
        d->h = h;
        dirty();
    }

    GLsizei Texture2D::getWidth() const
    {
        return d->w;
    }

    GLsizei Texture2D::getHeight() const
    {
        return d->h;
    }

    void Texture2D::setImage(const std::string &img)
    {
        d->img = img;
        dirty();
    }

    bool Texture2D::save(const std::string &path) const
    {
        return false;
    }

    GLuint Texture2D::onCreate(State& ctx)
    {
        GLuint id = 0;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        stbi_set_flip_vertically_on_load(true);
        if (d->img.size() > 0)
        {
            int w, h, channels;
            auto data = stbi_load(d->img.data(), &w, &h, &channels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        }
        else if (d->w != 0 && d->h != 0 && d->informat != 0)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, d->informat, d->w, d->h, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        }
        return id;
    }

    bool Texture2D::onUpdate(State& ctx)
    {
        return true;
    }

}