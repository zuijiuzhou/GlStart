#include "anyrenderer_global.h"
#include <iostream>
#include "Renderer.h"
#include "MeshShape.h"
#include "PointCloud.h"
#include "PointCloudLoader.h"
#include <Windows.h>

using namespace AnyRenderer;

void CreateSampleShapes(Renderer *renderer)
{
    std::vector<glm::vec3> vertices{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0)};
    std::vector<glm::vec3> normals{glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)};

    auto ms = new AnyRenderer::MeshShape();
    ms->setVertices(vertices);
    ms->setNormals(normals);

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
    auto pc = new AnyRenderer::PointCloud();
    pc->setData(pts, colors);
    renderer->addShape(ms);
    renderer->addShape(pc);
}

class A{
    public:
    int xx;
    A(int x):xx(x){}
    ~A(){
        std::cout << "A dctor." << xx << std::endl;
    }
};

void ThrowCPPEX(){
    A obj2(1);
    try{
    throw std::exception("123");
    }
    catch(...){


    }
}

void ThrowSEHEX(){
    A obj(2);
    try
    { 
        A obj2(3);
        auto a = 1, b = 0;
        std::cout << a / b;
    }
    catch(...)
    {
        std::cerr << "Cpp Catch:" << '\n';
        std::rethrow_exception(std::current_exception());
    }
}

void TestThrow(){
    // ThrowCPPEX();
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
    auto renderer = new AnyRenderer::Renderer();
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