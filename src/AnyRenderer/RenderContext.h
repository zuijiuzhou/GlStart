#pragma once
#include "Object.h"

namespace AnyRenderer
{
    class Renderer;
    class Camera;
    class Texture2D;
    class CubeMap;
    class Shader;
    class StateSet;

    class RenderContext : public Object
    {
        friend class Renderer;
        friend class StateSet;

    private:
        RenderContext(Camera *cam);
        virtual ~RenderContext();

    public:
        Camera *getCamera() const;
        Renderer *getRenderer() const;
        Shader *getCurrentShader() const;
        Texture2D *getDefaultTexture() const;
        CubeMap *getDefaultEnvMap() const;

        int getContextId() const;

        virtual void makeCurrent();

    public:
        static RenderContext *getContextById(int id);

    public:
        struct Data;

    private:
        Data *const d;
    };
}