#pragma once

namespace AnyRenderer
{
    class Renderer;
    class Camera;
    class Texture2D;
    class CubeMap;

    class RenderContext final
    {
        friend class Renderer;

    private:
        RenderContext();
        RenderContext(Camera *cam);
        virtual ~RenderContext();
    public:
        Camera *getCamera() const;
        Renderer* getRenderer() const;

        Texture2D* getDefaultTexture() const;
        CubeMap* getDefaultEnvMap() const;

    private:
        Camera *cam_ = nullptr;
        Renderer* renderer_ = nullptr;
        Texture2D* def_tex_ = nullptr;
        CubeMap* def_env_map_ = nullptr;
    };
}