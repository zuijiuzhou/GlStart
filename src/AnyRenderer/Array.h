#pragma once
#include "BufferData.h"
namespace AnyRenderer
{
    class Array : public BufferData
    {
        VI_OBJECT_META;

    public:
        enum Type
        {
            ARRAY_UNKNOW = 0,
            ARRAY_INT,
            ARRAY_UBYTE,
            ARRAY_USHORT,
            ARRAY_UINT,
            ARRAY_FLOAT,
            ARRAY_VEC2F,
            ARRAY_VEC3F,
            ARRAY_VEC4F
        };

    public:
        virtual ~Array();

    public:
        virtual Type getType() const = 0;
        virtual GLsizei getSize() const = 0;
        virtual GLsizei getSizeOfItem() const = 0;
        virtual void *getData() = 0;
        virtual void *getAt(GLsizei index) = 0;
        bool isEmpty() const;

    protected:
        virtual void onBind(State &state) override;
        virtual void onUnbind(State &state) override;
        virtual void onRelease(State &state) override;
    };
}