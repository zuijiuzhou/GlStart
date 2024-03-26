#pragma once

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
    private:
        struct Rep;
        Rep* const rep_;
    };
}