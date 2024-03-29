#pragma once
#include <string>

namespace osg{
    class MatrixTransform;
}

namespace ModelViewer{

class MeshLoader{
public:
    osg::MatrixTransform* loadFile(const std::string& file);
    
    static bool isSupported(const std::string& file);
};
}