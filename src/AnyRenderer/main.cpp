#include <iostream>
#include <Windows.h>
#include <QApplication>
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
#include "GlfwViewer.h"
#include "QtMainWindow.h"
#include "QtViewer.h"
#include "RefPtr.h"
#include "CubeMap.h"

namespace ar = AnyRenderer;

void CreateSampleShapes(ar::Renderer *renderer)
{
    auto cube = new ar::Group();
    {
        auto geom = ar::Geometry::createCube(0.6, 0, 1, -1, 3);
        auto colors = new ar::Vec4fArray();
        colors->emplace_back(0.8f, 0.8f, 0.8f, 1.0f);
        geom->addVertexAttribArray(2, colors);
        auto tex = ar::ResourceManager::instance()->getInternalCubeMap(ar::ResourceManager::ICM_CubeMap2);
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

int main(int argc, char **argv)
{
#define GLFW_VIEWER1

#ifdef GLFW_VIEWER
    ar::GlfwViewer v;
    auto renderer = v.getRenderer();
#else
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    ar::QtMainWindow wnd;
    auto renderer = wnd.getViewer()->getRenderer();
#endif

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
#ifdef GLFW_VIEWER
    v.run();
#else
    wnd.show();
    app.exec();
#endif
    return 0;
}