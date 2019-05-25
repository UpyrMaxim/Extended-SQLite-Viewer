#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // для передачи модели в qml
#include <QSqlDatabase>
#include <QtQuick/QQuickWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QFontDatabase>

#include "qsqlitetablelist.h"
#include "qsqlitemodel.h"
#include "qhexconvertor.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<QSQLiteModel>("SQliteModel", 1, 0, "SQliteModel");
    qmlRegisterType<QSQLiteTableList>("SQliteTableList", 1, 0, "SQliteTableList");
    qmlRegisterType<QHexConvertor>("QHexConvertor", 1, 0, "QHexConvertor");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    engine.rootContext()->setContextProperty("fixedFont", fixedFont);

//    MySQLTableModel model{};

//    engine.rootContext()->setContextProperty(QString("myTableDataModel"), &model);
    engine.load(url);

    return app.exec();
}
