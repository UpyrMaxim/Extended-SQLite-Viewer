#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // для передачи модели в qml
#include <QFontDatabase>

#include "qsqlitetablelist.h"
#include "qsqlitemodel.h"
#include "qhexconvertor.h"
#include "rawdatatable.h"

#include "rawdatabaseparserwrapper.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<QSQLiteModel>("SQliteModel", 1, 0, "SQliteModel");
    qmlRegisterType<QSQLiteTableList>("SQliteTableList", 1, 0, "SQliteTableList");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    std::vector<RawDataBaseParserWrapper*> RDBParser;
    RDBParser.emplace_back(new RawDataBaseParserWrapper());

    QHexConvertor hexConvertor(RDBParser.front());
    RAWDataTable rawDataTable(RDBParser.front());

    engine.rootContext()->setContextProperty(QString("QHexConvertor"), &hexConvertor);
    engine.rootContext()->setContextProperty(QString("RAWDataTable"), &rawDataTable);

    const QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    engine.rootContext()->setContextProperty("fixedFont", fixedFont);
    engine.load(url);

    return app.exec();
}
