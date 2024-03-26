#pragma once
#include <string>

namespace osg{
    class MatrixTransform;
}

namespace ModelViewer{

class BrepLoader{
public:
    static osg::MatrixTransform* loadStpFile(const std::string& path);    
};
}