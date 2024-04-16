#pragma once

namespace AnyRenderer
{
    class Renderer;
    class Camera;
    class Texture2D;
    class CubeMap;
    class Shader;
    class StateSet;

    class RenderContext final
    {
        friend class Renderer;
        friend class StateSet;
        
    private:
        RenderContext();
        RenderContext(Camera *cam);
        virtual ~RenderContext();
    public:
        Camera *getCamera() const;
        Renderer* getRenderer() const;
        Shader* getCurrentShader() const;
        Texture2D* getDefaultTexture() const;
        CubeMap* getDefaultEnvMap() const;


    private:
        Camera *cam_ = nullptr;
        Renderer* renderer_ = nullptr;
        Shader* current_shader_ = nullptr;

        Texture2D* def_tex_ = nullptr;
        CubeMap* def_env_map_ = nullptr;
    };
}