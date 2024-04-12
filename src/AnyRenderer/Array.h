#pragma once
#include "BufferData.h"
namespace AnyRenderer
{
    class Array : public BufferData
    {
    public:
        enum Type
        {
            Unknow = 0,
            IntArray,
            UByteArray,
            UShortArray,
            UIntArray,
            FloatArray,
            Vec2fArray,
            Vec3fArray,
            Vec4fArray
        };

    public:
        virtual ~Array();

    public:
        
        virtual Type getType() const = 0;
        virtual GLsizei getSize() const = 0;
        virtual GLsizei getSizeOfItem() const = 0;
        virtual void* getData() = 0;
        virtual void* getAt(GLsizei index) = 0;
        bool isEmpty() const;
    
    protected:
        virtual void onBind() override;
        virtual void onUnbind() override;
    };
}