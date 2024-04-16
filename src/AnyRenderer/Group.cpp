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

    BoundingBox Group::getBoundingBox() const{
        if(bb_is_dirty_){
            BoundingBox bb;
            for(auto d : drawables_){
                bb.combine(d->getBoundingBox());
            }
            auto this_ = const_cast<Group*>(this);
            this_->bb_ = bb;
            this_->bb_is_dirty_ = false;
        }
        return bb_;
    }

}