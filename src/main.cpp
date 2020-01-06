#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <src/ui_model/main_model.hpp>
#include <src/ui_model/tracks_list_model.hpp>
#include <QtQuickControls2/QQuickStyle>
#include "src/ui_model/track_note.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    MainModel mainModel;

    //Register type so that it can be used within QML
    qmlRegisterType<TracksListModel>("kompozitor", 1, 0, "TrackListModel");

    QQmlApplicationEngine engine;
    // This enables using the "mainModel" variable inside main.qml
    engine.rootContext()->setContextProperty("mainModel", &mainModel);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return QGuiApplication::exec();
}
