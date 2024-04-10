#pragma once

#include <vector>
#include <string>
#include "Texture.h"

namespace AnyRenderer
{
    class CubeMap : public Texture
    {
    public:
        CubeMap();
        virtual ~CubeMap();

    public:

        virtual Type getType() const override;
        void setImages(const std::vector<std::string> &imgs);

    protected:
        virtual void create() override;

        virtual void update() override;

    private:
        std::vector<std::string> imgs_;
    };
}