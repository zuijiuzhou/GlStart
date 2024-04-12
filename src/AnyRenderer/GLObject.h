#pragma once
#include <glad/glad.h>
#include "Object.h"

namespace AnyRenderer{
    class GLObject : public Object{
    public:
        GLuint getId() const;

        bool isCreated() const;

    protected:
        void create();
        virtual GLuint onCreate() = 0;

    private:
        GLuint id_ = 0;
    };
}