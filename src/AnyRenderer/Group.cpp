#include "Group.h"
#include "Drawable.h"

namespace AnyRenderer
{
    Group::~Group()
    {
        for (auto item : drawables_)
        {
            item->unref();
        }
    }

    void Group::addDrawable(Drawable *drawable)
    {
        drawables_.push_back(drawable);
        drawable->ref();
    }

    void Group::removeDrawable(Drawable *drawable)
    {
        auto found_at = std::find(drawables_.rbegin(), drawables_.rend(), drawable);
        if (found_at != drawables_.rend())
        {
            drawables_.erase(found_at.base());
            (*found_at.base())->unref();
        }
    }

    const std::vector<Drawable*>& Group::getDrawables() const{
        return drawables_;
    }
}