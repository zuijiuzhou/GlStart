
#pragma once
#include <vector>
#include <osg/Vec3d>

namespace osg{
    class MatrixTransform;
}
namespace ModelViewer{
    osg::MatrixTransform* createBSpline(std::vector<osg::Vec3d>& ctrl_points, std::vector<osg::Vec3d>& tangents);
}