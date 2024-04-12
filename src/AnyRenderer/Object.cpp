#include "Object.h"

namespace AnyRenderer
{
    void Object::ref()
    {
        // 单线程
        nb_refs_++;
    }
    void Object::unref()
    {
        nb_refs_--;
        if(nb_refs_ == 0)
            delete this;
    }
}