#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "DrawArea.h"

#include <QDirIterator>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DrawArea>("DrawDemo", 1, 0, "DrawArea");

    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        qDebug() << it.next();
    }

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/DrawDemo/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}