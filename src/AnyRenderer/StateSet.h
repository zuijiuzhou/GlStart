#pragma once
#include "Object.h"
#include "StateAttribute.h"

namespace AnyRenderer
{
    class StateAttribute;
    class Shader;
    class StateSet : public Object
    {
    public:
        StateSet();
        virtual ~StateSet();

    public:
        void setAttribute(StateAttribute *attr);

        StateAttribute *getAttribute(StateAttribute::Type type) const;

        size_t getNbAttributes() const;
        StateAttribute* getAttributeAt(size_t i);

        Shader *getShader() const;

        void setShader(Shader *shader);

    private:
        struct Data;
        Data *const d;
    };
}