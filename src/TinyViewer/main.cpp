#include "tinyviewer_global.h"
#include <iostream>
#include "Renderer.h"
#include "MeshShape.h"
#include "PointCloud.h"
#include "PointCloudLoader.h"
#include <Windows.h>

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

class A{
    public:
    ~A(){
        std::cout << "A析构" << std::endl;
    }
};

void ThrowCPPEX(){
    A obj2;
    try
    {
        throw std::exception("123");
    }
    catch(const std::exception& e)
    {
        std::cout << "CPP CATCH:" << e.what() << std::endl;
    }
    
}

void ThrowSEHEX(){
    A obj;
    try
    { A obj2;
        auto a = 1, b = 0;
        std::cout << a / b;
    }
    catch(...)
    {
        std::cerr << "Cpp Catch: 除0" << '\n';
    }
}

void TestThrow(){
    __try{
        ThrowSEHEX();
    }
    __except(EXCEPTION_EXECUTE_HANDLER){
        std::cout << "SEH Catch:" << std::endl;
    }
    // A a;
    // throw std::exception("TestThrow throw a exception\n");
}

int main(int argc, char **argv)
{
    TestThrow();
    return 0;
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