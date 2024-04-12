#include "Array.h"

#ifdef ArrayImpl

namespace AnyRenderer
{
    GLuint ArrayImpl::onCreate()
    {
        GLuint id = 0;
        glGenBuffers(GL_ARRAY_BUFFER, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size(), data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        return id;
    }

    Array::Type ArrayImpl::getType() const
    {
        if constexpr (std::is_same<float, item_type>::value)
        {
            return Array::FloatArray;
        }
        else if constexpr (std::is_same<int, item_type>::value)
        {
            return Array::IntArray;
        }
        else if constexpr (std::is_same<glm::vec2, item_type>::value)
        {
            return Array::Vec2fArray;
        }
        else if constexpr (std::is_same<glm::vec3, item_type>::value)
        {
            return Array::Vec3fArray;
        }
        else if constexpr (std::is_same<glm::vec4, item_type>::value)
        {
            return Array::Vec4fArray;
        }
        return Unknow;
    }

    GLsizei ArrayImpl::getSize() const
    {
        return static_cast<GLuint>(size());
    }

    GLsizei ArrayImpl::getSizeOfItem() const
    {
        return static_cast<GLuint>(sizeof(item_type));
    }

    void *ArrayImpl::getData()
    {
        return (void *)data();
    }

    void *ArrayImpl::getAt(GLsizei index)
    {
        return &at(index);
    }
}
#endif
