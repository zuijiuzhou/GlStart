#include <iostream>
#include <filesystem>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

#include "Utilities/Text.h"
#include "Utilities/Environment.h"

#include "Viewer.h"
#include "BrepLoader.h"
#include "MeshLoader.h"
#include "ModelDefs.h"

int main(int argc, char **argv)
{
    if (argc == 1)
        return -1;
    using namespace ModelViewer;

    namespace fs = std::filesystem;
    fs::current_path(Utilities::getApplicationDir());

    std::string file = argv[1];
    osg::Node* model = nullptr;
    if(MeshLoader::isSupported(file)){
        model = MeshLoader().loadFile(file);
    }
    else if(BrepLoader::isSupported(file)){
        // convet to utf-8
        model = BrepLoader().loadFile(file);
    }
    else{
        std::cout << std::endl << "Not supported." <<std::endl;
        return -2;
    }

    if(!model){
        std::cout << std::endl << "Load failed." <<std::endl;
        return -3;
    }
    
    Viewer v;
    // v.addNode(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0,0,0), 20, 50)));
    v.addNode(model);
    // v.addNode(model2);
    v.fitToSceen();
    v.run();

    return 0;
}