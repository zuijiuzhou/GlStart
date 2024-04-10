
#include "anyrenderer_global.h"
#include "Texture.h"

namespace AnyRenderer{

    Texture::~Texture(){

    }

    unsigned int Texture::getId() const{
        return id_;
    }

    bool Texture::isCreated() const{
        return id_ > 0;
    }

    void Texture::bind(){
        auto type = getType();
        if(!isCreated())
            create();
        if(!isCreated())
            return;
        if(isDirty())
            update();
        glBindTexture(type, id_);
    }

    void Texture::unbind(){
        auto type = getType();
        glBindTexture(type, 0);
    }

    void Texture::dirty(){
        is_dirty_ = true;
    }

    bool Texture::isDirty() const{
        return is_dirty_;
    }
}