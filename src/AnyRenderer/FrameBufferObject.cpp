#include "FrameBufferObject.h"

#include <map>

#include <vine/core/Ptr.h>
#include <vine/core/Exception.h>

#include "Texture2D.h"
#include "RenderBuffer.h"
#include "State.h"

namespace AnyRenderer
{
    VI_OBJECT_META_IMPL(FrameBufferObject, GLObject);

    struct FrameBufferObject::Data
    {
        std::map<BufferComponent, vine::RefPtr<PixelBuffer>> components;
    };

    FrameBufferObject::FrameBufferObject() : d(new Data())
    {
        
    }

    FrameBufferObject::~FrameBufferObject()
    {
        delete d;
    }

    void FrameBufferObject::attachRenderBuffer(BufferComponent comp, RenderBuffer* buffer) {
        if (getNbInstances()) {
            throw vine::Exception(vine::Exception::INVALID_OPERATION);
        }
        auto iter = d->components.find(comp);
        if (iter == d->components.end())
            d->components.insert({ comp, buffer });
        else
            iter->second = buffer;
    }

    void FrameBufferObject::attachTexture(BufferComponent comp, Texture* tex) {
        if (getNbInstances()) {
            throw vine::Exception(vine::Exception::INVALID_OPERATION);
        }
        auto iter = d->components.find(comp);
        if (iter == d->components.end())
            d->components.insert({ comp, tex });
        else
            iter->second = tex;
    }

    GLuint FrameBufferObject::onCreate(State& state)
    {
        GLuint id;
        glGenFramebuffers(1, &id);
        glBindFramebuffer(GL_FRAMEBUFFER, id);

        for (auto&& kv : d->components) {
            auto& buffer = kv.second;
            // ȷ������
            buffer->bind(state);
            if (buffer->isKindOf<Texture2D>()) {
                glFramebufferTexture2D(GL_FRAMEBUFFER, kv.first, GL_TEXTURE_2D, buffer->getId(state), 0);
            }
            else {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, kv.first, GL_RENDERBUFFER, buffer->getId(state));
            }
            buffer->unbind(state);
        }
        return id;
    }

    void FrameBufferObject::onRelease(State& state)
    {
        auto id = getId(state);
        glDeleteFramebuffers(1, &id);
    }
}