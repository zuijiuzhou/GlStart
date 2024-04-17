#pragma once
#include <vector>
#include "Node.h"
namespace AnyRenderer
{
    class Drawable;
    class Group : public Node
    {
    public:
        Group();
        virtual ~Group();

    public:
        void addDrawable(Drawable *drawable);

        void removeDrawable(Drawable *drawable);

        int getNbDrawables() const;

        Drawable* getDrawableAt(int index) const;

        virtual BoundingBox getBoundingBox() const override;

    private:
        struct Data;
        Data* const d;
    };
}