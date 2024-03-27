#pragma once
#include "ModelDefs.h"
namespace osg{
    class Node;
}

namespace ModelViewer{
    class Viewer{
    public:
        Viewer();
        void run();
        void fitToSceen();
        void addNode(osg::Node* node);
        void addNode(osg::Node* node, PipelineMask mask);

    private:
        struct Rep;
        Rep* const rep_;
    };
}