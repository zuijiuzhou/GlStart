#include "PointCloudLoader.h"
#include <filesystem>
#include <algorithm>
#include <locale>
#include <limits>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/features/normal_3d.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>

#include "Geometry.h"
#include "Model.h"
#include "ResourceManager.h"
#include "StateSet.h"

namespace AnyRenderer
{   
    using PCPtr = pcl::PointCloud<pcl::PointXYZRGBA>::Ptr;
    namespace
    {
        Model *parse(const PCPtr cloud)
        { 
            auto z_lower = 0.3f;
            auto z_upper = 0.5f;
            auto z_range = z_upper - z_lower;

            PCPtr cloud2(new pcl::PointCloud<pcl::PointXYZRGBA>());
            pcl::PassThrough<pcl::PointXYZRGBA> pass;
            pass.setInputCloud(cloud);
            pass.setFilterFieldName("z");
            pass.setFilterLimits(z_lower, z_upper);
            pass.filter(*cloud);
            pass.filter(*cloud2);

            std::vector<pcl::ModelCoefficients::Ptr> vec_plane_coefficients;
            std::vector<pcl::PointIndices::Ptr> vec_plane_indices;
            // pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
            // pcl::PointCloud<pcl::Normal>::Ptr cloud_normals(new pcl::PointCloud<pcl::Normal>);
            // pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>());

            // ne.setSearchMethod(tree);
            // ne.setInputCloud(cloud2);
            // ne.setKSearch(50);
            // ne.compute(*cloud_normals);
            
            // pcl::SACSegmentationFromNormals<pcl::PointXYZ, pcl::Normal> seg;
            pcl::SACSegmentation<pcl::PointXYZRGBA> seg;
            seg.setInputCloud(cloud2);
            seg.setModelType(pcl::SACMODEL_PLANE);
            seg.setMethodType(pcl::SAC_RANSAC);
            seg.setDistanceThreshold(0.001);
            seg.setMaxIterations(1000);
            seg.setOptimizeCoefficients(true);
            // seg.setRadiusLimits(0, 0.2);
            // seg.setEpsAngle(0.01);
            // seg.setInputNormals(cloud_normals);
            // pcl::ModelCoefficients::Ptr mcs(new pcl::ModelCoefficients());
            // pcl::PointIndices::Ptr indices(new pcl::PointIndices);
            // seg.segment(*indices, *mcs);
            while (true)
            {
                pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
                pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
                seg.segment(*inliers, *coefficients);
                if (!inliers->indices.size())
                    break;
                vec_plane_coefficients.push_back(coefficients);
                vec_plane_indices.push_back(inliers);
                pcl::ExtractIndices<pcl::PointXYZRGBA> extract1;
                extract1.setInputCloud(cloud2);
                extract1.setIndices(inliers);
                extract1.setNegative(true);
                extract1.filter(*cloud2);

                // pcl::ExtractIndices<pcl::Normal> extract2;
                // extract2.setInputCloud(cloud_normals);
                // extract2.setIndices(inliers);
                // extract2.setNegative(true);
                // extract2.filter(*cloud_normals);
            }

            auto geom = new Geometry();
            auto vertices = new Vec3fArray();
            auto colors = new Vec3fArray();
            vertices->reserve(cloud->size());
            colors->reserve(cloud->size());

            std::vector<glm::vec3> color_map;
            for(int i = 0; i < 256; i++){
                auto r = rand() / 32767.;
                auto g = rand() / 32767.;
                auto b = rand() / 32767.;
                color_map.emplace_back(r, g, b);
            }
            
            for(int i = 0; i < vec_plane_indices.size(); i++){
                auto indices = vec_plane_indices[i];
                for(auto idx : indices->indices){
                    auto& pt = (*cloud)[idx];
                    vertices->emplace_back(pt.x, pt.y, pt.z);
                    colors->emplace_back(color_map[i]);
                }
            }

            auto depth = 0.f;
            for(auto &&pt : *cloud){
                vertices->emplace_back(pt.x + 0.5, pt.y, pt.z);
                depth = (pt.z - z_lower) / z_range * 2.f;
                if(depth <= 1.f){
                    colors->emplace_back(1.f - depth, depth, 0.f);
                }
                else if(depth <= 2.f){
                    colors->emplace_back(0.f, 2.f - depth, depth - 1.f);
                }
            }

            for(auto &&pt : *cloud){
                vertices->emplace_back(pt.x - 0.5, pt.y, pt.z);
                colors->emplace_back(pt.r / 255., pt.r / 255., pt.r / 255.);
            }

            geom->addVertexAttribArray(0, vertices);
            geom->addVertexAttribArray(1, colors);
            geom->addPrimitive(new DrawArrays(DrawArrays::MODE_POINTS, 0, vertices->size()));

            auto pc = new Model();
            pc->addDrawable(geom);
            pc->getOrCreateStateSet()->setShader(ResourceManager::instance()->getInternalShader(ResourceManager::IS_PointCloud));
            
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
            auto pc = pcl::make_shared<pcl::PointCloud<pcl::PointXYZRGBA>>();
            pcl::io::loadPLYFile<pcl::PointXYZRGBA>(path, *pc);
            data_ = parse(pc);
        }
        else if (ext == ".pcd")
        {
            auto pc = pcl::make_shared<pcl::PointCloud<pcl::PointXYZRGBA>>();
            pcl::io::loadPCDFile<pcl::PointXYZRGBA>(path, *pc);
            data_ = parse(pc);
        }
    }

    Model *PointCloudLoader::getData() const
    {
        return data_;
    }
}