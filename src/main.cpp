#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <src/ui_model/main_model.hpp>
#include "src/ui_model/track_note.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MainModel mainModel;

    //Register type so that it can be used within QML
    qmlRegisterType<TrackNote>("kompozitor", 1, 0, "TrackNote");

    QQmlApplicationEngine engine;
    // This enables using the "mainModel" variable inside main.qml
    engine.rootContext()->setContextProperty("mainModel", &mainModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return QGuiApplication::exec();
}
