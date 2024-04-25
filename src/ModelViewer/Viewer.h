#pragma once
#include "ModelDefs.h"
namespace osg
{
    class Node;
    class Camera;
}

namespace ModelViewer
{
    class Viewer
    {
    public:
        Viewer();
        void run();
        void fitToSceen();
        void addNode(osg::Node *node);
        void addNode(osg::Node *node, PipelineMask mask);
        osg::Camera* getMasterCamera() const;

    private:
        struct Rep;
        Rep *const rep_;
    };
}