#pragma once
#include <string>

namespace AnyRenderer
{
    class Group;
    class PointCloudLoader
    {

    public:
        PointCloudLoader(const std::string &path);

    public:
        Group *getData() const;

    private:
        void load(const std::string &path);

    private:
        Group *data_ = nullptr;
    };
}