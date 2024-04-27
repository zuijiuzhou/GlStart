
#pragma once
#include <vector>
#include <osg/Vec3d>
#include <osg/Vec4>

namespace osg{
    class MatrixTransform;
}
namespace ModelViewer{
    osg::MatrixTransform* createBSpline(const std::vector<osg::Vec3d>& ctrl_points, const std::vector<double>& params, const std::vector<osg::Vec3d>& tangents, const osg::Vec4& color);

    osg::MatrixTransform* createBSpline(const std::vector<osg::Vec3d>& ctrl_points, const std::vector<double>& params, const osg::Vec4& color);
}