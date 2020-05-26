#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "client.h"

//#include "client.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    //qmlRegisterType<Client>("client.h", 1, 0, "Client");

    Client cl;
    qDebug() << cl.start(1234, QString("127.0.0.1"));
    qDebug() << cl.login("user3", "123");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
