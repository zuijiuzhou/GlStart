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
        virtual GLuint onCreate(RenderContext &ctx) override;
        virtual bool onUpdate(RenderContext &ctx) override;

    private:
        std::vector<std::string> imgs_;
    };
}