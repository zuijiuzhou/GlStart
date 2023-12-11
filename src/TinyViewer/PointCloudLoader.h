#pragma once
#include <string>

namespace TinyViewer
{
    class PointCloud;
    class PointCloudLoader
    {

    public:
        PointCloudLoader(const std::string &path);

    public:
        PointCloud *getData() const;

    private:
        void load(const std::string &path);

    private:
        PointCloud *data_ = nullptr;
    };
}