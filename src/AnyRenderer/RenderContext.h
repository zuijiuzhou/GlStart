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
    class GLObject;

    class RenderContext : public Object
    {
        friend class Renderer;
        friend class StateSet;

    protected:
        RenderContext(Camera *cam);
        virtual ~RenderContext();

    public:
        int getContextId() const;
        virtual void makeCurrent();
        Camera *getCamera() const;
        Renderer *getRenderer() const;
        Shader *getCurrentShader() const;
        Texture2D *getDefaultTexture() const;
        CubeMap *getDefaultEnvMap() const;
        void attachGLObject(GLObject *obj);
        void detachGLObject(GLObject *obj);
        void releaseGLObjects();

    public:
        static RenderContext *getContextById(int id);

    public:
        struct Data;

    private:
        Data *const d;
    };
}