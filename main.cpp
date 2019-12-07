#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ui_model/main_model.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    MainModel mainModel;

    QObject *rootObject = engine.rootObjects().first();
    auto *playButton = rootObject->findChild<QObject *>("play_button");
    QObject::connect(playButton, SIGNAL(clicked()), &mainModel, SLOT(playSomething()));

    return app.exec();
}
