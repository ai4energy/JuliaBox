#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "jluna.hpp"
int main(int argc, char *argv[])
{
    jluna::initialize(2, false,"d:/jjluna/bin/jluna.dll","","d:/ai4edll/ai4e.dll");
   //上面的函数，路径中盘符用小写。大写有问题
   
    jluna::Main.safe_eval("println(\"hello\")");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qtjluna/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
