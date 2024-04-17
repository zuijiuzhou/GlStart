#include "Node.h"
#include "StateSet.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct Node::Data
    {
        RefPtr<StateSet> state_set = nullptr;
        glm::mat4 matrix = glm::mat4(1.0);
    };

    Node::Node() : d(new Data())
    {
    }
    Node::~Node()
    {
        delete d;
    }

    glm::mat4 Node::getMatrix() const
    {
        return d->matrix;
    }

    void Node::setMatrix(const glm::mat4 &mat)
    {
        d->matrix = mat;
    }

    StateSet *Node::getOrCreateStateSet()
    {
        if (!d->state_set.get())
        {
            d->state_set = new StateSet();
        }
        return d->state_set.get();
    }

    StateSet *Node::getStateSet()
    {
        return d->state_set.get();
    }
}