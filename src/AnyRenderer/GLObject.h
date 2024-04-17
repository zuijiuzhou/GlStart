#pragma once
#include <glad/glad.h>
#include "Object.h"

namespace AnyRenderer
{
    class GLObject : public Object
    {
    public:
        GLObject();
        virtual ~GLObject();

    public:
        GLuint getId() const;

        bool isCreated() const;

    protected:
        void create();
        virtual GLuint onCreate() = 0;

    private:
        struct Data;
        Data *const d;
    };
}