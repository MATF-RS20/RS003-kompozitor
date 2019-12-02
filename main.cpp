#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ui_model/main_model.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    MainModel mainModel;

    auto *printButton = engine.rootObjects().first()->findChild<QObject *>("print_button");
    QObject::connect(printButton, SIGNAL(clicked()), &mainModel, SLOT(printSomething()));

    return app.exec();
}
