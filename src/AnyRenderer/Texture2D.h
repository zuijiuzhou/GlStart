#pragma once

#include <vector>
#include <string>
#include "Texture.h"

namespace AnyRenderer
{
    class Texture2D : public Texture
    {
    public:
        Texture2D();
        virtual ~Texture2D();

    public:

        virtual Type getType() const override;
        void setImage(const std::string& img);

    protected:
        virtual GLuint onCreate() override;

        virtual bool onUpdate() override;

    private:
        struct Data;
        Data* const d;
    };
}