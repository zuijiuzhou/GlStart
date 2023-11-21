#include "tinyviewer_global.h"

#include "Renderer.h"
#include "MeshShape.h"

int main(int argc, char **argv)
{
    std::vector<glm::vec3> vertices{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0)};
    std::vector<glm::vec3> normals{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)};

    auto ms = new TinyViewer::MeshShape();
    ms->setData(vertices, normals);
    ms->setColor(glm::vec4(1, 0, 1, 1));
    auto renderer = new TinyViewer::Renderer();
    renderer->addShape(ms);
    renderer->run();

    return 0;
}