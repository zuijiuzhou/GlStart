#include "Object.h"
#include <iostream>
namespace AnyRenderer
{

    Object::~Object()
    {
        if (nb_refs_ > 0)
        {

            printf("Warning:\n");
        }
    }

    void Object::ref()
    {
        // 单线程
        nb_refs_++;
    }
    void Object::unref()
    {
        nb_refs_--;
        if (nb_refs_ == 0)
            delete this;
    }
}