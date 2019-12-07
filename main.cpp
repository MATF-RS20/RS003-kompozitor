#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ui_model/main_model.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainModel mainModel;

    QQmlApplicationEngine engine;
    // This enables using the "mainModel" variable inside main.qml
    engine.rootContext()->setContextProperty("mainModel", &mainModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
