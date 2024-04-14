#pragma once
#include <string>

namespace AnyRenderer
{
    class Geometry;
    class PointCloudLoader
    {

    public:
        PointCloudLoader(const std::string &path);

    public:
        Geometry *getData() const;

    private:
        void load(const std::string &path);

    private:
        Geometry *data_ = nullptr;
    };
}