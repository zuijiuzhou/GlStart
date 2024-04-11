#include "CubeMap.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "anyrenderer_global.h"

namespace AnyRenderer
{

    CubeMap::CubeMap()
    {
    }

    CubeMap::~CubeMap()
    {
    }

    Texture::Type CubeMap::getType() const{
        return Type::TexCubeMap;
    }

    void CubeMap::setImages(const std::vector<std::string> &imgs)
    {
        imgs_ = imgs;
    }

    void CubeMap::create()
    {
        if (isCreated())
            return;
        if (imgs_.size() != 6)
            return;

        GLuint id = -1;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);
        stbi_set_flip_vertically_on_load(true);
        for (int i = 0; i < 6; i++)
        {
            auto& file = imgs_[i];
            int w, h, channels;
            auto data = stbi_load(file.data(), &w, &h, &channels, 0);
            if(data){
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        id_ = id;
    }

    void CubeMap::update()
    {
        if (!isCreated())
            return;
        is_dirty_ = false;
    }

}