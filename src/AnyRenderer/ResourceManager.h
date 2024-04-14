#pragma once
#include <string>

namespace AnyRenderer
{
    class Shader;
    class CubeMap;
    // 暂不考虑多上下文共享资源
    class ResourceManager
    {
    public:
        enum InternalShader
        {
            IS_Geometry = 1,
            IS_PointCloud = 2
        };

        enum InternalCubeMap{
            ICM_CubeMap1,
            ICM_CubeMap2
        };

    private:
        ResourceManager();

    public:
        Shader *getShader(const std::string &name);
        Shader *getInternalShader(InternalShader shader);
        CubeMap *getInternalCubeMap(InternalCubeMap map);

    public:
        static ResourceManager *instance();
    };
}