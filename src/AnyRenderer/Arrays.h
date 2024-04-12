#pragma once

#include "Array.h"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "anyrenderer_global.h"

namespace AnyRenderer
{

    #define DEF_ARR(N, T) \
        class N##Array : public Array, public std::vector<T>{ \
        public: \
            using item_type = T; \
        public: \
            virtual Type getType() const; \
            virtual GLsizei getSize() const override;\
            virtual GLsizei getSizeOfItem() const override;\
            virtual void *getData() override;\
            virtual void *getAt(GLsizei index) override; \
        protected: \
            virtual GLuint onCreate() override; \
            virtual bool onUpdate() override; \
        };

    DEF_ARR(Int, int)
    DEF_ARR(Float, float)
    DEF_ARR(Vec2f, glm::vec2)
    DEF_ARR(Vec3f, glm::vec3)
    DEF_ARR(Vec4f, glm::vec4)
} // namespace AnyRenderer
