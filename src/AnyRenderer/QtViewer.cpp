#include "QtViewer.h"
#include "Renderer.h"
#include "Camera.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct QtViewer::Data
    {
        RefPtr<Renderer> renderer = nullptr;
    };

    QtViewer::QtViewer()
        : d(new Data())
    {
    }

    QtViewer::~QtViewer()
    {
        delete d;
    }

    void QtViewer::initializeGL()
    {
        auto cam = d->renderer->getCamera();
        cam->setViewport(0., 0., width(), height());
        cam->setClearDepth(1.0);
        cam->setClearStencil(1);
        cam->setClearColor(glm::vec4(0., 0., 0., 1.));
        cam->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_PROGRAM_POINT_SIZE);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glDepthFunc(GL_LESS);
    }

    void QtViewer::resizeGL(int w, int h)
    {
        d->renderer->getCamera()->setViewport(0, 0, w, h);
    }

    void QtViewer::paintGL()
    {
        d->renderer->frame();
    }

    void QtViewer::resizeEvent(QResizeEvent *e)
    {
    }
}