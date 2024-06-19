#pragma once
#include <string>

#include "Object.h"

namespace AnyRenderer
{
    class Image : public Object
    {
        VI_OBJECT_META;

    public:
        enum Format{
            RGB,
            RGBA,
        };

    public:
        Image();

    public:
        void loadFile(const std::string &file);

        Format getFormat() const;

        unsigned char* data() const;

        bool isNull() const;

    public:
        static bool isSupported(const std::string &file);

    private:
        struct Data;
        Data* const d;
    };
}