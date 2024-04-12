#include "Texture2D.h"
#include <stb_image.h>
#include "anyrenderer_global.h"

namespace AnyRenderer
{

    Texture2D::Texture2D()
    {
    }

    Texture2D::~Texture2D()
    {
    }

    Texture::Type Texture2D::getType() const{
        return Type::Texture2D;
    }

    void Texture2D::setImage(const std::string& img)
    {
        img_ = img;
        setDirty(true);
    }

    GLuint Texture2D::onCreate()
    {
        GLuint id = 0;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        stbi_set_flip_vertically_on_load(true);
        int w, h, channels;
        auto data = stbi_load(img_.data(), &w, &h, &channels, 0);
        if(data){
            glTexImage2D(GL_TEXTURE_2D , 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
        return id;
    }

    bool Texture2D::onUpdate()
    {
        return true; 
    }

}