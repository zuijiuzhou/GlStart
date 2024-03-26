#include "Viewer.h"
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>

#include <osgVerse/Pipeline/SkyBox.h>
#include <osgVerse/Pipeline/Pipeline.h>
#include <osgVerse/Pipeline/LightModule.h>
#include <osgVerse/Pipeline/ShadowModule.h>

namespace ModelViewer
{

    class ViewerEx : public osgViewer::Viewer
    {
    public:
        ViewerEx()
        {
        }
    };

    struct Viewer::Rep
    {
        osg::ref_ptr<ViewerEx> impl_viewer;
        osg::ref_ptr<osg::Group> root;
    };
    Viewer::Viewer()
        : rep_(new Rep())
    {

        rep_->root = new osg::Group();
        rep_->impl_viewer = new ViewerEx();

        auto traits = new osg::GraphicsContext::Traits();
        traits->x = 100;
        traits->y = 100;
        traits->width = 1440;
        traits->height = 900;
        traits->windowDecoration = true;
        traits->supportsResize = true;
        traits->doubleBuffer = true;
        traits->depth = 24;
        traits->samples = 4;
        auto gc = osg::GraphicsContext::createGraphicsContext(traits);
        auto cam = rep_->impl_viewer->getCamera();
        cam->setGraphicsContext(gc);
        cam->setViewport(0, 0, traits->width, traits->height);
        cam->setProjectionMatrixAsPerspective(30, (double)traits->width / traits->height, 1, 1000);
        cam->setViewMatrixAsLookAt(osg::Vec3(200,0,0), osg::Vec3(), osg::Vec3(0, 1, 0));

        auto camm = new osgGA::TrackballManipulator();
        // camm->setAutoComputeHomePosition(false);
        // camm->setByMatrix(cam->getViewMatrix());

        // rep_->impl_viewer->setCameraManipulator(camm);
        rep_->impl_viewer->addEventHandler(new osgViewer::StatsHandler());
        rep_->impl_viewer->addEventHandler(new osgViewer::WindowSizeHandler());
        rep_->impl_viewer->addEventHandler(new osgGA::StateSetManipulator(rep_->impl_viewer->getCamera()->getOrCreateStateSet()));
        // rep_->impl_viewer->setUpViewInWindow(0, 0, 1444, 900, 0);
        rep_->impl_viewer->setSceneData(rep_->root);
    }

    void Viewer::run()
    {
        rep_->impl_viewer->run();
    }

    void Viewer::addNode(osg::Node *node)
    {
        rep_->root->addChild(node);
    }

    void Viewer::fitToSceen(){
        // auto cm = rep_->impl_viewer->getCameraManipulator();
        // cm->computeHomePosition(rep_->impl_viewer->getCamera());
        // cm->home(0);
    }
}