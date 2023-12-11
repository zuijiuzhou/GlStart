#include "tinyviewer_global.h"

#include "Renderer.h"
#include "MeshShape.h"
#include "PointCloud.h"
#include "PointCloudLoader.h"

using namespace TinyViewer;

void CreateSampleShapes(Renderer *renderer)
{
    std::vector<glm::vec3> vertices{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0)};
    std::vector<glm::vec3> normals{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)};

    auto ms = new TinyViewer::MeshShape();
    ms->setData(vertices, normals);
    ms->setColor(glm::vec4(1, 0, 1, 1));

    std::vector<glm::vec3> pts;
    std::vector<glm::vec3> colors;
    pts.reserve(1000);
    colors.reserve(pts.capacity());
    auto posi_offset = INT16_MAX / 10000.f / 2.f;
    for (size_t i = 0; i < pts.capacity(); i++)
    {
        pts.emplace_back(rand() / 10000. - posi_offset, rand() / 10000. - posi_offset, rand() / 10000.);
        colors.emplace_back(rand() / static_cast<double>(INT16_MAX), rand() / static_cast<double>(INT16_MAX), rand() / static_cast<double>(INT16_MAX));
    }
    auto pc = new TinyViewer::PointCloud();
    pc->setData(pts, colors);
    renderer->addShape(ms);
    renderer->addShape(pc);
}

int main(int argc, char **argv)
{

    auto renderer = new TinyViewer::Renderer();
    if (argc > 1)
    {
        auto file = argv[1];
        auto pcl = new PointCloudLoader(file);
        renderer->addShape(pcl->getData());
    }
    else
    {
        CreateSampleShapes(renderer);
    }
    renderer->run();

    return 0;
}