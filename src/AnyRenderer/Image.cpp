#include "Image.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(Image, Object);

    struct Image::Data
    {
        unsigned char *data = nullptr;
        Format format;
    };

    Image::Image()
        : d(new Data())
    {
    }

    void Image::loadFile(const std::string &file)
    {
    }

    Image::Format Image::getFormat() const
    {
        return d->format;
    }

    unsigned char *Image::data() const
    {
        return d->data;
    }

    bool Image::isNull() const
    {
        return d->data == nullptr;
    }

    bool Image::isSupported(const std::string &file)
    {
        return false;
    }
}