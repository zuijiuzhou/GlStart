#include "RenderContext.h"
#include "Utilities/Resources.h"
#include "Texture2D.h"
#include "CubeMap.h"
#include "ResourceManager.h"
#include "RefPtr.h"
#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"

namespace AnyRenderer
{

    struct RenderContext::Data
    {
        static int max_context_id;
        GLuint context_id;
        RefPtr<Camera> camera;
        RefPtr<Renderer> renderer;
        RefPtr<Shader> current_shader;
        RefPtr<Texture2D> default_tex;
        RefPtr<CubeMap> default_env_map;
    };

    int RenderContext::Data::max_context_id = 0;

    extern void RenderContext_set_shader(RenderContext::Data *d, Shader *shader)
    {
        d->current_shader = shader;
    }

    RenderContext::RenderContext(Camera *cam) : d(new Data())
    {
        d->camera = cam;
        d->default_tex = new Texture2D();
        d->default_tex->setImage(__RES("/images/top.jpg"));
        d->default_env_map = ResourceManager::instance()->getInternalCubeMap(ResourceManager::ICM_CubeMap2);
        d->context_id = ++Data::max_context_id;
    }

    RenderContext::~RenderContext()
    {
        delete d;
    }

    Camera *RenderContext::getCamera() const
    {
        return d->camera.get();
    }

    Renderer *RenderContext::getRenderer() const
    {
        return d->renderer.get();
    }

    Shader *RenderContext::getCurrentShader() const
    {
        return d->current_shader.get();
    }

    Texture2D *RenderContext::getDefaultTexture() const
    {
        return d->default_tex.get();
    }

    CubeMap *RenderContext::getDefaultEnvMap() const
    {
        return d->default_env_map.get();
    }

    int RenderContext::getContextId() const
    {
        return d->context_id;
    }

    void RenderContext::makeCurrent(){
        
    }

    RenderContext *RenderContext::getContextById(int id)
    {
        return nullptr;
    }
}