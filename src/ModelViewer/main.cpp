#include <iostream>
#include <filesystem>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

#include "Utilities/Text.h"
#include "Utilities/Environment.h"

#include "Viewer.h"
#include "BrepLoader.h"
#include "ModelDefs.h"

int main(int argc, char **argv)
{
    if (argc == 1)
        return -1;
    using namespace ModelViewer;

    namespace fs = std::filesystem;
    fs::current_path("G:\\projs\\GlStart\\vsc_build\\bin\\Release");

    // convet to utf-8
    auto u8path = Utilities::gbkToUtf8(argv[1]);
    auto model = BrepLoader::loadStpFile(u8path);


    // auto model2 = BrepLoader::loadStpFile((char*)u8"r:/models/2030023074779焊接1.STEP");
    // model2->setMatrix(osg::Matrixd::translate(osg::Vec3d(400,0,-100)));

    Viewer v;
    // v.addNode(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0,0,0), 20, 50)));
    v.addNode(model);
    // v.addNode(model2);
    v.fitToSceen();
    v.run();

    return 0;
}