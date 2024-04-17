#include "GLObject.h"

namespace AnyRenderer
{
    struct GLObject::Data
    {
        GLuint id = 0;
    };

    GLObject::GLObject() : d(new Data())
    {
    }
    GLObject::~GLObject()
    {
        delete d;
    }
    GLuint GLObject::getId() const
    {
        return d->id;
    }

    void GLObject::create()
    {
        if (isCreated())
            return;
        d->id = onCreate();
    }

    bool GLObject::isCreated() const
    {
        return d->id > 0;
    }

}