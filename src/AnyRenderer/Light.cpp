#include "Light.h"
#include "Shader.h"
#include "RenderContext.h"
#include "Camera.h"

namespace AnyRenderer
{
    Light::Light()
        : a_(glm::vec4(0.05f, 0.05f, 0.05f, 1.0f)), d_(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f)), s_(glm::vec4(0.05f, 0.05f, 0.05f, 1.0f)), pos_(glm::vec4(0.f, 0.f, 1.f, 0.0f)), dir_(glm::vec3(0.f, 0.f, -1.f)), k_c_(1.0f), k_l_(0.0f), k_q_(0.0f), expo_(0.f), co_(180)
    {
    }
    glm::vec4 Light::getAmbient() const
    {
        return a_;
    }
    void Light::setAmbient(const glm::vec4 &color)
    {
        a_ = color;
    }

    glm::vec4 Light::getDiffuse() const
    {
        return d_;
    }
    void Light::setDiffuse(const glm::vec4 &color)
    {
        d_ = color;
    }

    glm::vec4 Light::getSpecular() const
    {
        return s_;
    }
    void Light::setSpecular(const glm::vec4 &color)
    {
        s_ = color;
    }

    glm::vec3 Light::getDirection() const
    {
        return dir_;
    }
    void Light::setDirection(const glm::vec3 &dir)
    {
        dir_ = glm::normalize(dir);
    }

    glm::vec4 Light::getPosition() const
    {
        return pos_;
    }
    void Light::setPosition(const glm::vec4 &pos)
    {
        pos_ = pos;
    }

    float Light::getConstantAttenuation() const
    {
        return k_c_;
    }
    void Light::setConstantAttenuation(float val)
    {
        k_c_ = val;
    }

    float Light::getLinearAttenuation() const
    {
        return k_l_;
    }
    void Light::setLinearAttenuation(float val)
    {
        k_l_ = val;
    }

    float Light::getQuadraticAttenuation() const
    {
        return k_q_;
    }
    void Light::settQuadraticAttenuation(float val)
    {
        k_q_ = val;
    }

    float Light::getCutoff() const
    {
        return co_;
    }
    void Light::setCutoff(float val)
    {
        co_ = val;
    }

    float Light::getExponent() const
    {
        return expo_;
    }
    void Light::setExponent(float val)
    {
        expo_ = val;
    }

    void Light::setIsHead(bool head)
    {
        head_ = head;
    }

    bool Light::getIsHead() const
    {
        return head_;
    }

    void Lights::addLight(Light *l)
    {
        if (!l)
            return;
        auto found_at = std::find(lights_.begin(), lights_.end(), l);

        if (found_at != lights_.end())
        {
            if (*found_at == l)
                return;
            lights_.erase(found_at);
        }
        lights_.push_back(l);
    }
    void Lights::removeLight(Light *l)
    {
        if (!l)
            return;
        auto found_at = std::find(lights_.begin(), lights_.end(), l);

        if (found_at != lights_.end())
        {
            lights_.erase(found_at);
        }
    }
    std::vector<Light *> Lights::getLights() const
    {
        return lights_;
    }

    StateAttribute::Type Lights::getType() const
    {
        return ATTR_LIGHTS;
    }

    void Lights::apply(RenderContext &ctx) const
    {
        auto shader = ctx.getCurrentShader();
        if (shader)
        {
            auto max_light = getMaxLight();
            for (int i = 0; i < lights_.size(); i++)
            {
                if (i >= max_light)
                    break;
                auto l = lights_[i];
                auto prefix = "lights[" + std::to_string(i) + "]";
                shader->set(ctx, prefix + ".a", l->getAmbient());
                shader->set(ctx, prefix + ".d", l->getDiffuse());
                shader->set(ctx, prefix + ".s", l->getSpecular());
                shader->set(ctx, prefix + ".k_c", l->getConstantAttenuation());
                shader->set(ctx, prefix + ".k_l", l->getLinearAttenuation());
                shader->set(ctx, prefix + ".k_q", l->getQuadraticAttenuation());
                shader->set(ctx, prefix + ".expo", l->getExponent());
                shader->set(ctx, prefix + ".co", l->getCutoff());

                auto dir = l->getDirection();
                auto pos = l->getPosition();
                if(l->getIsHead()){
                    dir = ctx.getCamera()->getViewDir();
                    auto view_pos = ctx.getCamera()->getViewPos();
                    pos.x = view_pos.x;
                    pos.y = view_pos.y;
                    pos.z = view_pos.z;
                }
                shader->set(ctx, prefix + ".dir", dir);
                shader->set(ctx, prefix + ".pos", pos);
            }
            shader->set<int>(ctx, "lights_count", lights_.size() > max_light ? max_light : lights_.size());
        }
    }

    int Lights::getMaxLight()
    {
        return 8;
    }
}