#include <QApplication>
#include "mainform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat surface;
    //surface.setMajorVersion(4);
    //surface.setMinorVersion(3);
    //surface.setSamples(16);
    //surface.setProfile(QSurfaceFormat::CoreProfile);

    MainForm w;
    w.setFormat(surface);
    w.resize(1024,512);
    w.setMaximumSize(QSize(1024,512));
    w.setMinimumSize(QSize(1024,512));
    w.show();

    w.setAnimating(true);

    return a.exec();
}
