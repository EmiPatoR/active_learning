#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    QString locale = QLocale::system().name().section('_', 0, 0);
    translator.load(QApplication::applicationDirPath() + QString("/languages/al_") + locale);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
