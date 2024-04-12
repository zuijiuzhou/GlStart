#pragma once

namespace AnyRenderer
{
    class Object
    {

    public:
        void ref();
        void unref();

    private:
        unsigned int nb_refs_ = 0;
    };
}