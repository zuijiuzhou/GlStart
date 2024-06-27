#pragma once

#include "Buffer.h"

namespace AnyRenderer
{
    class RenderBufferBase : public Buffer
    {
        VI_OBJECT_META;

    public:
        enum InternalFormat{
            // 1-CHANNEL
            IF_R8 = GL_R8,
            IF_R16 = GL_R16,
            IF_R16F = GL_R16F,
            IF_R16I = GL_R16I,
            IF_R16UI = GL_R16UI,

            IF_RED = GL_RED,
            IF_GREEN = GL_GREEN,
            IF_BLUE = GL_BLUE,

            // 3-CHANNELS
            IF_RGB = GL_RGB,
            // RGB8
            IF_RGB8 = GL_RGB8,
            IF_RGB8I = GL_RGB8I,
            IF_RGB8UI = GL_RGB8UI,
            // RGB10
            IF_RGB10 = GL_RGB10,
            // RGB12
            IF_RGB12 = GL_RGB12,
            // RGB16
            IF_RGB16 = GL_RGB16,
            IF_RGB16I = GL_RGB16I,
            IF_RGB16UI = GL_RGB16UI,
            IF_RGB16F = GL_RGB16F,
            // RGB32
            IF_RGB32I = GL_RGB32I,
            IF_RGB32UI = GL_RGB32UI,
            IF_RGB32F = GL_RGB32F,

            // 4-CHANNELS
            IF_RGBA = GL_RGBA,
            // RGBA8
            IF_RGBA8 = GL_RGBA8,
            IF_RGBA8I = GL_RGBA8I,
            IF_RGBA8UI = GL_RGBA8UI,
            // RGBA12
            IF_RGBA12 = GL_RGBA12,
            // RGBA16
            IF_RGBA16 = GL_RGBA16,
            IF_RGBA16I = GL_RGBA16I,
            IF_RGBA16UI = GL_RGBA16UI,
            // RGBA32
            IF_RGBA32I = GL_RGBA32I,
            IF_RGBA32UI = GL_RGBA32UI,
            IF_RGBA32F = GL_RGBA32F,

            // SRGB
            IF_SRGB = GL_SRGB,
            IF_SRGB8 = GL_SRGB8,

            // BRG
            IF_BGR = GL_BGR,
            IF_BGRA = GL_BGRA,
            
            // DEPTH
            IF_DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
            IF_DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
            IF_DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
            IF_DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
            IF_DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,

            // STENCIL
            IF_STENCIL_INDEX = GL_STENCIL_INDEX,
            IF_STENCIL_INDEX8 = GL_STENCIL_INDEX8,
            IF_STENCIL_INDEX16 = GL_STENCIL_INDEX16,

            // DEPTH_STENCIL
            IF_DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
            IF_DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8
        };

    public:
        RenderBufferBase();

    private:
        VI_OBJECT_DATA;
    };
}