#pragma once
#include "StateAttribute.h"
#include <glm/vec4.hpp>
namespace AnyRenderer
{
    class Material : public StateAttribute
    {
        public:
        Material();

    public:
        glm::vec4 getAmbient() const;
        void setAmbient(const glm::vec4& color);

        glm::vec4 getDiffuse() const;
        void setDiffuse(const glm::vec4& color);

        glm::vec4 getSpecular() const;
        void setSpecular(const glm::vec4& color);

        glm::vec4 getEmission() const;
        void setEmission(const glm::vec4& color);

        float getShininess() const;
        void setShininess(float shininess);

        Type getType() const;
    
        virtual void apply(const RenderContext& ctx) const override;
        
    private:
        glm::vec4 a_, d_, s_, e_;
        float sh_;
    };
}