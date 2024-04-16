#include "Node.h"
#include "StateSet.h"

namespace AnyRenderer
{
    Node::~Node()
    {
        if (state_set_)
            state_set_->unref();
    }

    glm::mat4 Node::getMatrix() const
    {
        return matrix_;
    }

    void Node::setMatrix(const glm::mat4 &mat)
    {
        matrix_ = mat;
    }

    StateSet *Node::getOrCreateStateSet()
    {
        if (!state_set_)
        {
            state_set_ = new StateSet();
            state_set_->ref();
        }
        return state_set_;
    }

    StateSet *Node::getStateSet()
    {
        return state_set_;
    }
}