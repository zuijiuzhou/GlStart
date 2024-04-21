#pragma once
namespace AnyRenderer
{
    class Geometry;
    class CubeMap;
    static Geometry* createSkyBox(CubeMap* tex);
}