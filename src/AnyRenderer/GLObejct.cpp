#include "GLObject.h"

namespace AnyRenderer
{
    GLuint GLObject::getId() const
    {
        return id_;
    }

    void GLObject::create(){
        if(isCreated())
            return;
        id_ = onCreate();
    }

    bool GLObject::isCreated() const
    {
        return id_ > 0;
    }

}