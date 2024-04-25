
#pragma once
#include <osg/Vec3d>

namespace osg{
    class MatrixTransform;
}
namespace ModelViewer{
    osg::MatrixTransform* createCoord(double axis_len, bool auto_rotate_to_screen);
}