#include <iostream>
#include <Windows.h>
#include <QApplication>
#include <glm/glm.hpp>

#include <vine/core/Ptr.h>
#include <vine/ge/Rect2d.h>

#include "Utilities/Resources.h"
#include "Renderer.h"
#include "Geometry.h"
#include "PointCloudLoader.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "StateSet.h"
#include "Material.h"
#include "Light.h"
#include "Model.h"
#include "MeshLoader.h"
#include "Camera.h"
#include "GlfwViewer.h"
#include "QtMainWindow.h"
#include "QtViewer.h"
#include "CubeMap.h"
#include "GraphicContext.h"
#include "SkyBox.h"
#include "Shader.h"
#include "Viewer.h"
#include "Image.h"
#include "Uniform.h"

namespace ar = AnyRenderer;

void CreateSampleShapes(ar::Renderer *renderer)
{
    auto axis = new ar::Model();
    {
        auto geom =  new ar::Geometry();
        auto vertices = new ar::Vec3fArray();
        {
            vertices->push_back(glm::vec3());
            vertices->push_back(glm::vec3(10,0,0));
            vertices->push_back(glm::vec3());
            vertices->push_back(glm::vec3(0,10,0));
            vertices->push_back(glm::vec3());
            vertices->push_back(glm::vec3(0,0,10));
        }
        geom->addVertexAttribArray(0, vertices);
        auto colors = new ar::Vec4fArray();{
            colors->emplace_back(1.f, 0.f, 0.0f, 1.0f);
            colors->emplace_back(1.f, 0.f, 0.0f, 1.0f);
            colors->emplace_back(0.f, 1.f, 0.0f, 1.0f);
            colors->emplace_back(0.f, 1.f, 0.0f, 1.0f);
            colors->emplace_back(0.f, 0.f, 1.0f, 1.0f);
            colors->emplace_back(0.f, 0.f, 1.0f, 1.0f);
        }
        geom->addVertexAttribArray(2, colors);
        geom->addPrimitive(new ar::DrawArrays(ar::PrimitiveSet::MODE_LINES, 0, vertices->size()));
        axis->addDrawable(geom);
        axis->getOrCreateStateSet()->setAttribute(new ar::Material());
        axis->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_Base));
        axis->getOrCreateStateSet()->setAttribute(new ar::Uniform("use_texture", false));
    }

    auto cube = new ar::Model();
    {
        auto geom = ar::Geometry::createCube(1, 0, 1, -1, 3);
        auto colors = new ar::Vec4fArray();
        colors->emplace_back(0.8f, 0.8f, 0.8f, 1.0f);
        geom->addVertexAttribArray(2, colors);
        auto tex = ar::ResourceManager::instance()->getInternalCubeMap(ar::ResourceManager::ICM_CubeMap1);
        geom->addTexture(GL_TEXTURE0, "tex", tex);

        auto light = new ar::Light();
        light->setPosition(glm::vec4(10, 10, 10, 1.));
        light->setDirection(glm::vec3(2, 4, -1));
        light->setIsHead(true);
        auto lights = new ar::Lights();
        lights->addLight(light);

        cube->addDrawable(geom);
        glm::mat4 m1(1.f);
        m1 = glm::rotate(m1, glm::radians(90.f), glm::vec3(1.0f, 0.f, 0.f));
        cube->setMatrix(m1);
        cube->getOrCreateStateSet()->setAttribute(new ar::Material());
        cube->getOrCreateStateSet()->setAttribute(lights);
        cube->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_Geometry));
    }

    auto skybox = ar::createSkyBox(ar::ResourceManager::instance()->getInternalCubeMap(ar::ResourceManager::ICM_CubeMap2));

    auto pc = new ar::Model();
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


    auto img = new ar::Model();
    {
        auto tex = new ar::Texture2D();
        tex->setImage("C:\\Users\\sa\\Downloads\\1.jpg");
        auto geom_img = ar::Geometry::createTexturedQuad(0, 1, 3, vine::ge::Rect2d(0, 0, tex->getWidth(), tex->getHeight()), vine::ge::Rect2d(0, 0, 1, 1));
        geom_img->addTexture(0, "tex", tex);
        img->addDrawable(geom_img);
        img->getOrCreateStateSet()->setAttribute(new ar::Uniform("use_texture", true));
        img->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_Base));
    }

    renderer->addModel(axis);
    renderer->addModel(pc);
    renderer->addModel(cube);
    renderer->addModel(skybox);
    renderer->addModel(img);
}

#pragma pack(push, 1) //Save the current alignment and set a new one
struct Data{
    float x;
    float y;
    float z;
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
#pragma pack(pop)  // Restore the saved alignment

int main(int argc, char **argv)
{
#define GLFW_VIEWER1

#ifdef GLFW_VIEWER
    ar::GlfwViewer v;
    v.initialize();
    auto renderer = v.getViewer()->getRendererAt(0);
#else
    // QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts, false);
    QApplication app(argc, argv);
    ar::QtMainWindow wnd;
    auto renderer = wnd.getViewer()->getViewer()->getRendererAt(0);
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
        model->getOrCreateStateSet()->setAttribute(new ar::Uniform("use_texture", false));
        model->getOrCreateStateSet()->setShader(ar::ResourceManager::instance()->getInternalShader(ar::ResourceManager::IS_Base));
        renderer->addModel(model);

    }
    else
    {
        CreateSampleShapes(renderer);
    }

    auto x = renderer->isKindOf<vine::Object>();
    auto y = renderer->toString();
    std::cout << 1 << std::endl;

#ifdef GLFW_VIEWER
    v.run();
#else
    wnd.show();
    app.exec();
#endif
    return 0;
}