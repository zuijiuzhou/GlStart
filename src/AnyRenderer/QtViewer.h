#pragma once
#include <glad/glad.h>
#include <QOpenGLWidget>
#
namespace AnyRenderer
{
    class Renderer;
    class QtViewer : public QOpenGLWidget
    {
    public:
        QtViewer();
        virtual ~QtViewer();

    public:
    protected:
        virtual void initializeGL() override;
        virtual void resizeGL(int w, int h) override;
        virtual void paintGL() override;
        void resizeEvent(QResizeEvent *e) override;

    private:
        struct Data;
        Data *const d;
    };
}