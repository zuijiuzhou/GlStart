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
        ViewerEx(osgVerse::Pipeline *pipeline)
            : pipeline_(pipeline)
        {
        }

    protected:
        virtual osg::GraphicsOperation *createRenderer(osg::Camera *camera)
        {
            if (pipeline_.valid())
                return pipeline_->createRenderer(camera);
            else
                return osgViewer::Viewer::createRenderer(camera);
        }

    private:
        osg::ref_ptr<osgVerse::Pipeline> pipeline_;
    };

    struct Viewer::Rep
    {
        osg::ref_ptr<ViewerEx> viewer_impl;
        osg::ref_ptr<osg::Group> root;
    };
    Viewer::Viewer()
        : rep_(new Rep())
    {
        static bool is_verse_initialized = false;
        if(!is_verse_initialized){
            osgVerse::globalInitialize(0, 0);
            is_verse_initialized = true;
        }
        auto pipeline = new osgVerse::Pipeline();
        rep_->root = new osg::Group();
        rep_->viewer_impl = new ViewerEx(pipeline);

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
        traits->screenNum = 1;
        auto gc = osg::GraphicsContext::createGraphicsContext(traits);

        auto cam = rep_->viewer_impl->getCamera();
        cam->setGraphicsContext(gc);
        cam->setViewport(0, 0, traits->width, traits->height);
        cam->setProjectionMatrixAsPerspective(30, (double)traits->width / traits->height, 1, 1000);
        cam->setViewMatrixAsLookAt(osg::Vec3(200, 0, 0), osg::Vec3(), osg::Vec3(0, 1, 0));

        auto camm = new osgGA::TrackballManipulator();
        camm->setAutoComputeHomePosition(false);
        camm->setByMatrix(cam->getViewMatrix());

        rep_->viewer_impl->setCameraManipulator(camm);
        rep_->viewer_impl->addEventHandler(new osgViewer::StatsHandler());
        rep_->viewer_impl->addEventHandler(new osgViewer::WindowSizeHandler());
        rep_->viewer_impl->addEventHandler(new osgGA::StateSetManipulator(rep_->viewer_impl->getCamera()->getOrCreateStateSet()));
        rep_->viewer_impl->setThreadingModel(osgViewer::Viewer::SingleThreaded);
        rep_->viewer_impl->setSceneData(rep_->root);

        // Main light
        auto light0 = new osgVerse::LightDrawable;
        light0->setColor(osg::Vec3(1.0f, 1.0f, 1.0f));
        light0->setDirection(osg::Vec3(0.02f, 0.1f, -1.0f));
        light0->setDirectional(true);
        light0->setEyeSpace(false);

        auto light1 = new osgVerse::LightDrawable;
        light1->setColor(osg::Vec3(1.5f, 1.5f, 1.5f));
        light1->setDirection(osg::Vec3(1.f, 0.1f, 0.0f));
        light1->setDirectional(true);
        light1->setEyeSpace(false);

        auto lightGeode = new osg::Geode;
        lightGeode->addDrawable(light0);
        // lightGeode->addDrawable(light1);
        addNode(lightGeode);

        class ViewerEventCallback : public osgGA::GUIEventHandler{
        public:
            ViewerEventCallback(osgVerse::LightDrawable* light0)
                : light0_(light0){
                
            }
            virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*) override {
                if(ea.getEventType() == osgGA::GUIEventAdapter::FRAME){
                    osg::Vec3 eye, center, up, dir;
                    aa.asView()->getCamera()->getViewMatrixAsLookAt(eye, center, up);
                    // dir = center - eye;
                    dir = -eye;
                    dir.normalize();
                    // dir = dir * osg::Matrix::rotate(osg::PI_4 / 4, up);
                    light0_->setDirection(dir);
                }
                return false;
            }
        private:
            osgVerse::LightDrawable* light0_;
        };

        rep_->viewer_impl->addEventHandler(new ViewerEventCallback(light0));

        osgVerse::StandardPipelineParameters params(SHADER_DIR, SKYBOX_DIR "monoLake.hdr");
        params.enablePostEffects = true;
        params.enableAO = false;
        osgVerse::setupStandardPipeline(pipeline, rep_->viewer_impl.get(), params);

        // // Post pipeline settings
        // auto shadow = static_cast<osgVerse::ShadowModule*>(pipeline->getModule("Shadow"));
        // if (shadow && shadow->getFrustumGeode())
        // {
        //     addNode(shadow->getFrustumGeode(), PM_ForwardScene);
        // }

        auto light = static_cast<osgVerse::LightModule*>(pipeline->getModule("Light"));
        if (light) light->setMainLight(light0, "Shadow");
    }

    void Viewer::run()
    {
        rep_->viewer_impl->run();
    }

    void Viewer::addNode(osg::Node* node){
        osgVerse::TangentSpaceVisitor tsv;
        node->accept(tsv);
        rep_->root->addChild(node);
    }

    void Viewer::addNode(osg::Node *node, PipelineMask mask)
    {
        osgVerse::Pipeline::setPipelineMask(*node, mask);
        rep_->root->addChild(node);
    }

    void Viewer::fitToSceen()
    {
        auto cm = rep_->viewer_impl->getCameraManipulator();
        cm->computeHomePosition(rep_->viewer_impl->getCamera());
        cm->home(0);
    }
}