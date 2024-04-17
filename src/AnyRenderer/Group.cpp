#include "Group.h"
#include "Drawable.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct Group::Data
    {

        std::vector<RefPtr<Drawable>> drawables;
        BoundingBox bb;
        bool bb_is_dirty = true;
    };
    Group::Group() : d(new Data())
    {
    }

    Group::~Group()
    {
        delete d;
    }

    void Group::addDrawable(Drawable *drawable)
    {
        d->drawables.push_back(drawable);
    }

    void Group::removeDrawable(Drawable *drawable)
    {
        auto found_at = std::find(d->drawables.rbegin(), d->drawables.rend(), drawable);
        if (found_at != d->drawables.rend())
        {
            d->drawables.erase(found_at.base());
        }
    }

    int Group::getNbDrawables() const
    {
        return d->drawables.size();
    }

    Drawable *Group::getDrawableAt(int index) const
    {
        return d->drawables.at(index).get();
    }

    BoundingBox Group::getBoundingBox() const
    {
        if (d->bb_is_dirty)
        {
            BoundingBox bb;
            for (auto d : d->drawables)
            {
                bb.combine(d->getBoundingBox());
            }
            auto this_ = const_cast<Group *>(this);
            this_->d->bb = bb;
            this_->d->bb_is_dirty = false;
        }
        return d->bb;
    }

}