#include "QtMainWindow.h"

namespace AnyRenderer
{
    struct QtMainWindow::Data
    {
        QtViewer *viewer;
    };

    QtMainWindow::QtMainWindow() : d(new Data)
    {
    }

    QtMainWindow::~QtMainWindow()
    {
        delete d;
    }
}