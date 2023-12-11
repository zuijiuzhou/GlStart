#include "PointCloudLoader.h"
#include <filesystem>
#include <algorithm>
#include <locale>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>

#include "PointCloud.h"

namespace TinyViewer
{
    namespace
    {
        PointCloud *parse(pcl::PointCloud<pcl::PointXYZ>* pts)
        {
            auto pc = new PointCloud();
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> colors;

            vertices.reserve(pts->size());
            colors.reserve(pts->size());


            auto z_lower = 0.3f;
            auto z_upper = 0.5f;
            auto z_range = z_upper - z_lower;


            auto depth = 0.f;
            for(auto &&pt : *pts){
                if(pt.z > z_upper || pt.z < z_lower)
                    continue;
                vertices.emplace_back(pt.x, pt.y, pt.z);
                depth = (pt.z - z_lower) / z_range * 2.f;
                if(depth <= 1.f){
                    colors.emplace_back(1.f - depth, depth, 0.f);
                }
                else if(depth <= 2.f){
                    colors.emplace_back(0.f, 2.f - depth, depth - 1.f);
                }
            }

            pc->setData(vertices, colors);

            return pc;
        }
    };

    PointCloudLoader::PointCloudLoader(const std::string &path)
    {
        load(path);
    }

    void PointCloudLoader::load(const std::string &path)
    {
        std::filesystem::path p(path);
        auto ext = p.extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (ext == ".ply")
        {
            auto pc = pcl::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
            pcl::io::loadPLYFile<pcl::PointXYZ>(path, *pc);
            data_ = parse(pc.get());
        }
        else if (ext == ".pcd")
        {
            auto pc = pcl::make_shared<pcl::PointCloud<pcl::PointXYZ>>();
            pcl::io::loadPCDFile<pcl::PointXYZ>(path, *pc);
            data_ = parse(pc.get());
        }
    }

    PointCloud *PointCloudLoader::getData() const
    {
        return data_;
    }
}