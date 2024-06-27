//#include "RenderBuffer.h"
//
//#include <vine/core/Ptr.h>
//
//#include "FrameBufferObject.h"
//
//namespace AnyRenderer{
//
//    namespace {
//        struct RenderBufferData {
//            vine::RefPtr<FrameBufferObject> fbo = nullptr;
//        };
//    }
//
//    extern void RenderBuffer_set_FrameBuffer(void* data, FrameBufferObject* fbo) {
//        auto d = (RenderBufferData*)data;
//        d->fbo = fbo;
//    }
//
//    VI_OBJECT_META_IMPL(RenderBuffer, RenderBufferBase);
//
//
//    struct RenderBuffer::Data : public RenderBufferData {
//        
//    };
//
//    RenderBuffer::RenderBuffer() :d(new Data()) {
//
//    }
//
//    FrameBufferObject* RenderBuffer::getFrameBuffer() const
//    {
//        return d->fbo.get();
//    }
//
//    bool RenderBuffer::onUpdate(State& state)
//    {
//        return false;
//    }
//
//    void RenderBuffer::onBind(State& state)
//    {
//        glBindRenderbuffer(GL_RENDERBUFFER, getId(state));
//    }
//
//    void RenderBuffer::onUnbind(State& state)
//    {
//        glBindRenderbuffer(GL_RENDERBUFFER, 0);
//    }
//}