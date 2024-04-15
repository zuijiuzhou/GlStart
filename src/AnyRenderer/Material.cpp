#include "Material.h"
#include "RenderContext.h"
#include "Shader.h"

namespace AnyRenderer
{
    Material::Material()
        : a_(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f))
        , d_(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f))
        , s_(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
        , e_(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
        , sh_(32.0f)
    {
    }

    glm::vec4 Material::getAmbient() const
    {
        return a_;
    }

    void Material::setAmbient(const glm::vec4 &color)
    {
        a_ = color;
    }

    glm::vec4 Material::getDiffuse() const
    {
        return d_;
    }

    void Material::setDiffuse(const glm::vec4 &color)
    {
        d_ = color;
    }

    glm::vec4 Material::getSpecular() const
    {
        return s_;
    }

    void Material::setSpecular(const glm::vec4 &color)
    {
        s_ = color;
    }

    glm::vec4 Material::getEmission() const
    {
        return e_;
    }

    void Material::setEmission(const glm::vec4 &color)
    {
        e_ = color;
    }

    float Material::getShininess() const
    {
        return sh_;
    }

    void Material::setShininess(float shininess)
    {
        sh_ = shininess;
    }

    StateAttribute::Type Material::getType() const
    {
        return ATTR_MATERIAL;
    }

    void Material::apply(const RenderContext &ctx) const
    {
        auto shader = ctx.getCurrentShader();
        if (shader)
        {
            shader->set("mate.a", a_);
            shader->set("mate.d", d_);
            shader->set("mate.s", s_);
            shader->set("mate.e", e_);
            shader->set("mate.sh", sh_);
        }
    }

}