#pragma once
#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include "StateAttribute.h"

namespace AnyRenderer
{
    class RenderContext;
    class Light : public Object
    {
    public:
        Light();

    public:
        glm::vec4 getAmbient() const;
        void setAmbient(const glm::vec4 &color);

        glm::vec4 getDiffuse() const;
        void setDiffuse(const glm::vec4 &color);

        glm::vec4 getSpecular() const;
        void setSpecular(const glm::vec4 &color);

        glm::vec3 getDirection() const;
        void setDirection(const glm::vec3 &dir);

        glm::vec4 getPosition() const;
        void setPosition(const glm::vec4 &pos);

        float getConstantAttenuation() const;
        void setConstantAttenuation(float val);

        float getLinearAttenuation() const;
        void setLinearAttenuation(float val);

        float getQuadraticAttenuation() const;
        void settQuadraticAttenuation(float val);

        float getCutoff() const;
        void setCutoff(float val);

        float getExponent() const;
        void setExponent(float val);

    private:
        glm::vec4 a_, d_, s_;
        glm::vec4 pos_;
        glm::vec3 dir_;
        float k_c_, k_l_, k_q_;
        float expo_, cutoff_;
    };

    class Lights : public StateAttribute
    {
    public:
        void addLight(Light *l);
        void removeLight(Light *l);
        std::vector<Light*> getLights() const;

        virtual void apply(const RenderContext& ctx) const override;

        virtual Type getType() const override;

        public:
        static int getMaxLight();
    private:
        std::vector<Light *> lights_;
    };
}