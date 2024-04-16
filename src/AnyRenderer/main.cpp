#include "anyrenderer_global.h"
#include <iostream>
#include "Utilities/Resources.h"
#include "Renderer.h"
#include "Geometry.h"
#include "PointCloudLoader.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "StateSet.h"
#include "Material.h"
#include "Light.h"
#include "Group.h"
#include "MeshLoader.h"
#include "Camera.h"
#include <Windows.h>

namespace ar = AnyRenderer;

void CreateSampleShapes(ar::Renderer *renderer)
{
    auto cube = new ar::Group();
    {
        auto geom = ar::Geometry::createCube(0.6, 0, 1, 3);
        auto colors = new ar::Vec4fArray();
        colors->emplace_back(0.8f, 0.8f, 0.8f, 1.0f);
        geom->addVertexAttribArray(2, colors);
        auto tex = new ar::Texture2D();
        tex->setImage(__RES("images/top.jpg"));
        geom->addTexture(GL_TEXTURE0, tex);

        auto light = new ar::Light();
        light->setPosition(glm::vec4(10, 10, 10, 1.));
        light->setDirection(glm::vec3(2, 4, -1));
        light->setIsHead(true);
        auto lights = new ar::Lights();
        lights->addLight(light);

        cube->addDrawable(geom);
        cube->getOrCreateStateSet()->setAttribute(new ar::Material());
        cube->getOrCreateStateSet()->setAttribute(lights);
        cube->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_Geometry));
    }

    auto pc = new ar::Group();
    {
        pc->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_PointCloud));
        auto geom = new ar::Geometry();
        auto vertices = new ar::Vec3fArray();
        auto colors = new ar::Vec3fArray();
        vertices->reserve(1000);
        colors->reserve(vertices->capacity());
        auto posi_offset = INT16_MAX / 10000.f / 2.f;
        for (size_t i = 0; i < vertices->capacity(); i++)
        {
            vertices->emplace_back(rand() / 10000. - posi_offset, rand() / 10000. - posi_offset, rand() / 10000.);
            colors->emplace_back(rand() / static_cast<double>(INT16_MAX), rand() / static_cast<double>(INT16_MAX), rand() / static_cast<double>(INT16_MAX));
        }
        geom->addVertexAttribArray(0, vertices);
        geom->addVertexAttribArray(1, colors);
        geom->addPrimitive(new ar::DrawArrays(ar::DrawArrays::MODE_POINTS, 0, vertices->size()));
        pc->addDrawable(geom);
    }
    renderer->addModel(pc);
    renderer->addModel(cube);
}

class A
{
public:
    int xx;
    A(int x) : xx(x) {}
    ~A()
    {
        std::cout << "A dctor." << xx << std::endl;
    }
};

void ThrowCPPEX()
{
    A obj2(1);
    try
    {
        throw std::exception("123");
    }
    catch (...)
    {
    }
}

void ThrowSEHEX()
{
    A obj(2);
    try
    {
        A obj2(3);
        auto a = 1, b = 0;
        std::cout << a / b;
    }
    catch (...)
    {
        std::cerr << "Cpp Catch:" << '\n';
        std::rethrow_exception(std::current_exception());
    }
}

void TestThrow()
{
    // ThrowCPPEX();
    __try
    {
        ThrowSEHEX();
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        std::cout << "SEH Catch:" << std::endl;
    }
    // A a;
    // throw std::exception("TestThrow throw a exception\n");
}

int main(int argc, char **argv)
{
    auto renderer = new ar::Renderer();
    if (argc > 1)
    {
        auto file = argv[1];
        // auto pcl = new ar::PointCloudLoader(file);
        // renderer->addModel(pcl->getData());

        auto model = ar::MeshLoader().loadFile(file);
        auto light = new ar::Light();
        light->setPosition(glm::vec4(10, 10, 10, 1.));
        light->setDirection(glm::vec3(2, 4, -1));
        light->setIsHead(true);
        auto lights = new ar::Lights();
        lights->addLight(light);
        model->getOrCreateStateSet()->setAttribute(new ar::Material());
        model->getOrCreateStateSet()->setAttribute(lights);
        model->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_Geometry));
        renderer->addModel(model);
    }
    else
    {
        CreateSampleShapes(renderer);
    }
    renderer->run();

    return 0;
}