#pragma once
#include <vector>
#include "Node.h"
namespace AnyRenderer
{
    class Drawable;
    class Group : public Node
    {
    public:
        virtual ~Group();

    public:
        void addDrawable(Drawable *drawable);

        void removeDrawable(Drawable *drawable);

        const std::vector<Drawable*>& getDrawables() const;

        virtual BoundingBox getBoundingBox() const override;
    private:
        std::vector<Drawable*> drawables_;
        BoundingBox bb_;
        bool bb_is_dirty_ = true;
    };
}