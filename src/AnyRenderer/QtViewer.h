#pragma once
#include <QOpenGLWidget>

namespace AnyRenderer
{
    class Viewer;
    class QtViewer : public QOpenGLWidget
    {
    public:
        QtViewer();
        virtual ~QtViewer();

    public:
        Viewer *getViewer() const;

    protected:
        virtual void initializeGL() override;
        virtual void resizeGL(int w, int h) override;
        virtual void paintGL() override;
        void resizeEvent(QResizeEvent *e) override;

        virtual void mousePressEvent(QMouseEvent *event) override;
        virtual void mouseReleaseEvent(QMouseEvent *event) override;
        virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
        virtual void mouseMoveEvent(QMouseEvent *event) override;
        virtual void wheelEvent(QWheelEvent *event) override;

    private:
        struct Data;
        Data *const d;
    };
}