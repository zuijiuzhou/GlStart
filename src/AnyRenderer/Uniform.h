#pragma once
#include <string>
#include "StateAttribute.h"
namespace AnyRenderer
{
    class Uniform : public StateAttribute
    {
        VI_OBJECT_META;

    public:
        enum ValueType{
            UNDEFINED = 0,
            BOOL,
            INT
        };

    public:
        Uniform();
        Uniform(const std::string &name, int val);
        Uniform(const std::string &name, bool val);

        virtual ~Uniform();

    public:
        virtual void apply(State &state) const override;

        virtual Type getType() const override;

    private:
        VI_OBJECT_DATA;
    };
}