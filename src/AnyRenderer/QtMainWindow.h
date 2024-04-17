#pragma once
#include <QMainWindow>
#
namespace AnyRenderer
{
    class QtViewer;
    class QtMainWindow : public QMainWindow
    {
    public:
        QtMainWindow();
        virtual ~QtMainWindow();

    public:
    protected:
    private:
        struct Data;
        Data *const d;
    };
}