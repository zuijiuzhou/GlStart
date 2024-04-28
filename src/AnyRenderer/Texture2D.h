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

        void setWidth(GLsizei w);

        void setHeight(GLsizei h);

        GLsizei getWidth() const;

        GLsizei getHeight() const;

        void setImage(const std::string &img);

        bool save(const std::string &path) const;

    protected:
        virtual GLuint onCreate(State& state) override;

        virtual bool onUpdate(State& state) override;

    private:
        struct Data;
        Data *const d;
    };
}