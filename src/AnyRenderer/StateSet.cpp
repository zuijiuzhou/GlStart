#include "StateSet.h"
#include "StateAttribute.h"
#include "RenderContext.h"

namespace AnyRenderer
{
    void StateSet::setAttribute(StateAttribute *attr)
    {
        if (!attr)
            return;
        auto type = attr->getType();
        auto is_set = false;
        for (auto &item : state_attrs)
        {

            auto item_type = item->getType();
            if (item_type == StateAttribute::ATTR_UNIFORM)
            {
            }
            else if (item_type == type)
            {
                item->unref();
                item = attr;
                item->ref();
                is_set = true;
                break;
            }
        }
        if (!is_set)
        {
            state_attrs.push_back(attr);
            attr->ref();
        }
    }

    void StateSet::apply(const RenderContext &ctx) const
    {
        for(auto attr : state_attrs){
            attr->apply(ctx);
        }
    }
}