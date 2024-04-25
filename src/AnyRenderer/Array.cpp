
#include "anyrenderer_global.h"
#include "Array.h"

namespace AnyRenderer{

    Array::~Array(){
         
    }

    void Array::onBind(RenderContext& ctx){
        glBindBuffer(GL_ARRAY_BUFFER, getId(ctx));
    }

    void Array::onUnbind(RenderContext& ctx){
        GLint current_id = 0;
        glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &current_id);
        if(current_id == getId(ctx))
            glBindTexture(GL_ARRAY_BUFFER, 0);
    }

    void Array::onRelease(RenderContext& ctx){
        auto id = getId(ctx);
        glDeleteBuffers(1, &id);
    }

    bool Array::isEmpty() const{
        return getSize() == 0;
    }
}