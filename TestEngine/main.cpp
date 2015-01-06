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
    w.resize(480,320);
    w.setMaximumSize(QSize(480,320));
    w.setMinimumSize(QSize(480,320));
    w.show();

    w.setAnimating(true);

    return a.exec();
}
