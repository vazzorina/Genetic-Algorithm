#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "datageneration.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DataGenerator generator;
    engine.rootContext()->setContextProperty("dataGenerator", &generator);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("geneticAlgorithm", "Main");

    return app.exec();
}
