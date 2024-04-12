#include "PrimitiveSet.h"

namespace AnyRenderer
{
    using Mode = PrimitiveSet::Mode;

    PrimitiveSet::PrimitiveSet()
    {
    }

    PrimitiveSet::PrimitiveSet(Mode mode, GLint insts) : mode_(mode), instances_(insts)
    {
    }

    Mode PrimitiveSet::getMode() const
    {
        return mode_;
    }

    void PrimitiveSet::setMode(Mode mode)
    {
        mode_ = mode;
    }

    GLint PrimitiveSet::getInstances() const
    {
        return instances_;
    }

    void PrimitiveSet::setInstances(GLint insts)
    {
        instances_ = insts;
    }

    DrawArrays::DrawArrays()
    {
    }

    DrawArrays::DrawArrays(Mode mode, GLint offset, GLsizei count) : DrawArrays(mode, offset, count, 1)
    {
    }

    DrawArrays::DrawArrays(Mode mode, GLint offset, GLsizei count, GLint insts) : PrimitiveSet(mode, insts), offset_(offset), count_(count)
    {
    }

    GLint DrawArrays::getOffset() const
    {
        return offset_;
    }

    void DrawArrays::setOffset(GLint offset)
    {
        offset_ = offset;
    }

    GLsizei DrawArrays::getCount() const
    {
        return count_;
    }

    void DrawArrays::setCount(GLsizei count)
    {
        count = count;
    }

    void DrawArrays::draw()
    {
        auto mode = getMode();
        auto insts = getInstances();

        if (insts > 1)
        {
            glDrawArraysInstanced(mode, offset_, count_, insts);
        }
        else
        {
            glDrawArrays(mode, offset_, count_);
        }
    }

    DrawElements::DrawElements()
    {
    }

    DrawElements::DrawElements(Mode mode) : DrawElements(mode, 1)
    {
    }

    DrawElements::DrawElements(Mode mode, GLint insts) : PrimitiveSet(mode, insts)
    {
    }

    void DrawElements::setIndices(Array *indices)
    {
        indices_ = indices;
    }

    Array *DrawElements::getIndices() const
    {
        return indices_;
    }

    void DrawElements::draw()
    {
        if (!indices_)
            return;
        auto mode = getMode();
        auto insts = getInstances();
        auto type = 0;
        auto arr_type = indices_->getType();
        if (arr_type == Array::UByteArray)
        {
            type = GL_UNSIGNED_BYTE;
        }
        else if (arr_type == Array::UShortArray)
        {
            type = GL_UNSIGNED_SHORT;
        }
        else if (arr_type == Array::UIntArray)
        {
            type = GL_UNSIGNED_INT;
        }
        if (insts > 1)
        {
            glDrawElementsInstanced(mode, indices_->getSize(), type, 0, insts);
        }
        else
        {
            glDrawElements(mode, indices_->getSize(), type, 0);
        }
    }
}