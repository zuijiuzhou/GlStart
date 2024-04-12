
#include "anyrenderer_global.h"
#include "Array.h"

namespace AnyRenderer{

    Array::~Array(){
        auto id = getId();
        if(id){
            glDeleteBuffers(1, &id);
        }
    }

    void Array::onBind(){
        glBindBuffer(GL_ARRAY_BUFFER, getId());
    }

    void Array::onUnbind(){
        GLint current_id = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current_id);
        if(current_id == getId())
            glBindTexture(GL_ARRAY_BUFFER, 0);
    }

    bool Array::isEmpty() const{
        return getSize() == 0;
    }
}