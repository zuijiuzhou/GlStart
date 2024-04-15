#include "RenderContext.h"
#include "Texture2D.h"
#include "CubeMap.h"
#include "Utilities/Resources.h"
#include "ResourceManager.h"

namespace AnyRenderer
{
    RenderContext::RenderContext() : RenderContext(nullptr){

    }

    RenderContext::RenderContext(Camera *cam) : cam_(cam)
    {
        def_tex_ = new Texture2D();
        def_tex_->setImage(__RES("/images/top.jpg"));
        def_env_map_ = ResourceManager::instance()->getInternalCubeMap(ResourceManager::ICM_CubeMap2);
    }

    RenderContext::~RenderContext(){
        delete def_tex_;
        delete def_env_map_;
    }

    Camera *RenderContext::getCamera() const
    {
        return cam_;
    }

    Renderer* RenderContext::getRenderer() const {
        return renderer_;
    }

    Shader* RenderContext::getCurrentShader() const{
        return current_shader_;
    }

    Texture2D* RenderContext::getDefaultTexture() const{
        return def_tex_;
    }
        
    CubeMap* RenderContext::getDefaultEnvMap() const{
        return def_env_map_;
    }
}