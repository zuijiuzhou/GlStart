#include "ModelDefs.h"
#include <osgVerse/Pipeline/Pipeline.h>

namespace ModelViewer{
    void setPipelineMask(osg::Node* node, PipelineMask mask){
        osgVerse::Pipeline::setPipelineMask(*node, mask);
    }
}