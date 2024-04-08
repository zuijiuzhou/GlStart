#pragma once

namespace osg{
    class Node;
}

namespace ModelViewer
{
    enum ModelMask
    {
        MM_All = 0xffffffff,
        MM_Zero = 0,
    };

    enum PipelineMask{
        PM_None,
        PM_DeferredScene = 0xff000000,
        PM_ForwardScene = 0x000000ff,
        PM_FixedShading = 0x00001000,
        PM_ShadowCaster = 0x10000000
    };

    void setPipelineMask(osg::Node* node, PipelineMask mask);
}