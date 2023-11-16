#include "tinyviewer_global.h"

#include "Renderer.h"
#include "MeshShape.h"

int main(int argc, char ** argv)
{
    TinyViewer::MeshShape* ms = new TinyViewer::MeshShape();
    TinyViewer::Renderer renderer;
    renderer.addShape(ms);
    renderer.run();
    return 0;
}