#include <iostream>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include "Viewer.h"
#include "BrepLoader.h"

int main(int argc, char** argv){
    using namespace ModelViewer;

    if(argc == 1)
        return -1;

    auto model = BrepLoader::loadStpFile(argv[1]);

    Viewer v;
    // v.addNode(model);
    // v.addNode(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0,0,0), 20, 50)));
    v.addNode(model);
    v.fitToSceen();
    v.run();
    
    return 0;
}