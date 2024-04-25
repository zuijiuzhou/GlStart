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
#include "CurveGenerator.h"

int main(int argc, char **argv)
{
    using namespace ModelViewer;
    osg::Node *model = nullptr;
    if (argc == 1 || true)
    {
        std::vector<osg::Vec3d> cpts;
        std::vector<osg::Vec3d> tans;

        cpts.push_back(osg::Vec3d(0, 0, 100));
        cpts.push_back(osg::Vec3d(0, 10, 100));
        cpts.push_back(osg::Vec3d(0, 20, 40));
        cpts.push_back(osg::Vec3d(0, 30, 42));
        cpts.push_back(osg::Vec3d(0, 40, 30));
        cpts.push_back(osg::Vec3d(0, 50, 40));
        cpts.push_back(osg::Vec3d(0, 60, 43));
        cpts.push_back(osg::Vec3d(0, 70, 100));
        cpts.push_back(osg::Vec3d(0, 80, 110));
        cpts.push_back(osg::Vec3d(0, 90, 120));
        cpts.push_back(osg::Vec3d(0, 100, 130));
        cpts.push_back(osg::Vec3d(0, 110, 130));

        tans.push_back(osg::Vec3d(0, 1, 0));
        tans.push_back(osg::Vec3d(0, 1, 0));

        model = createBSpline(cpts, tans);

    }
    else
    {
        std::string file = argv[1];
        if (MeshLoader::isSupported(file))
        {
            model = MeshLoader().loadFile(file);
        }
        else if (BrepLoader::isSupported(file))
        {
            // convet to utf-8
            model = BrepLoader().loadFile(file);
        }
        else
        {
            std::cout << std::endl
                      << "Not supported." << std::endl;
            return -2;
        }

        if (!model)
        {
            std::cout << std::endl
                      << "Load failed." << std::endl;
            return -3;
        }
    }

    namespace fs = std::filesystem;
    fs::current_path(Utilities::getApplicationDir());

    Viewer v;
    // v.addNode(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0,0,0), 20, 50)));
    v.addNode(model);
    // v.addNode(model2);
    v.fitToSceen();
    v.run();

    return 0;
}