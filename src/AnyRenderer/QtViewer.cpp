#include <glad/glad.h>
#include "QtViewer.h"
#include <QMouseEvent>
#include <QOpenGLContext>
#include <QApplication>
#include "Renderer.h"
#include "Camera.h"
#include "CameraManipulator.h"
#include "RefPtr.h"

namespace AnyRenderer
{
    struct QtViewer::Data
    {
        RefPtr<Renderer> renderer;
        RefPtr<CameraManipulator> cm;
    };

    QtViewer::QtViewer()
        : d(new Data())
    {
        setMouseTracking(true);
        setFocusPolicy(Qt::StrongFocus);
        QSurfaceFormat format;
        format.setProfile(QSurfaceFormat::CoreProfile);
        format.setSamples(4);
        format.setVersion(4, 6);
        format.setDepthBufferSize(24);
        format.setStencilBufferSize(8);
        format.setColorSpace(QSurfaceFormat::ColorSpace::DefaultColorSpace);
        format.setRenderableType(QSurfaceFormat::RenderableType::OpenGL);
        setFormat(format);

        auto renderer = new Renderer();
        auto cam = renderer->getCamera();
        auto cm = new StandardCameraManipulator(cam);

        d->renderer = renderer;
        d->cm = cm;
    }

    QtViewer::~QtViewer()
    {
        delete d;
    }

    Renderer *QtViewer::getRenderer() const
    {
        return d->renderer.get();
    }

    void QtViewer::initializeGL()
    {
        static auto ctx = context();
        static bool is_glad_loaded = false;
        if (!is_glad_loaded)
        {
            if (gladLoadGLLoader((GLADloadproc)[](const char *name) { return (void *)ctx->getProcAddress(name); }))
                is_glad_loaded = true;
            else
                throw std::exception("GLAD init faild.");
        }

        d->renderer->initialize();
        auto cam = d->renderer->getCamera();
        cam->setViewport(0, 0, width(), height());
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
        auto ratio = this->screen()->devicePixelRatio();
        d->cm->notifyResized(w * ratio, h * ratio);
    }

    void QtViewer::paintGL()
    {
        d->renderer->frame();
    }

    void QtViewer::resizeEvent(QResizeEvent *e)
    {
        QOpenGLWidget::resizeEvent(e);
    }

    void QtViewer::mousePressEvent(QMouseEvent *event)
    {
        auto btn = ButtonLeft;
        if (event->button() == Qt::LeftButton)
        {
            btn = ButtonLeft;
        }
        else if (event->button() == Qt::MiddleButton)
        {
            btn = ButtonMiddle;
        }
        else if (event->button() == Qt::RightButton)
        {
            btn = ButtonRight;
        }
        auto ratio = this->screen()->devicePixelRatio();
        d->cm->notifyMousePressed(btn, event->x() * ratio, event->y() * ratio);
        QOpenGLWidget::mousePressEvent(event);
        this->update();
    };

    void QtViewer::mouseReleaseEvent(QMouseEvent *event)
    {
        auto btn = ButtonLeft;
        if (event->button() == Qt::LeftButton)
        {
            btn = ButtonLeft;
        }
        else if (event->button() == Qt::MiddleButton)
        {
            btn = ButtonMiddle;
        }
        else if (event->button() == Qt::RightButton)
        {
            btn = ButtonRight;
        }
        auto ratio = this->screen()->devicePixelRatio();
        d->cm->notifyMouseReleased(btn, event->x() * ratio, event->y() * ratio);
        QOpenGLWidget::mouseReleaseEvent(event);
    };

    void QtViewer::mouseDoubleClickEvent(QMouseEvent *event)
    {
        QOpenGLWidget::mouseDoubleClickEvent(event);
        this->update();
    };

    void QtViewer::mouseMoveEvent(QMouseEvent *event)
    {
        auto ratio = this->screen()->devicePixelRatio();
        d->cm->notifyMouseMoved(event->x() * ratio, event->y() * ratio);
        QOpenGLWidget::mouseMoveEvent(event);
        this->update();
    };

    void QtViewer::wheelEvent(QWheelEvent *event)
    {
        d->cm->notifyMouseScrolled(event->angleDelta().y() / 20);
        QOpenGLWidget::wheelEvent(event);
        this->update();
    };
}