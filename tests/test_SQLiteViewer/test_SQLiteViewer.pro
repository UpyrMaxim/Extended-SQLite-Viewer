QT += testlib
QT += gui
QT += sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    ../../Extended_SQLite_Viewer/dbasesingleton.cpp \
    ../../Extended_SQLite_Viewer/qhexconvertor.cpp \
    ../../Extended_SQLite_Viewer/qsqlitemodel.cpp \
    ../../Extended_SQLite_Viewer/qsqlitetablelist.cpp \
    ../../Extended_SQLite_Viewer/rawdatabaseparserwrapper.cpp \
    ../../Extended_SQLite_Viewer/rawdatatable.cpp \
    tst_test_sqlite_viewer.cpp

HEADERS += \
    ../../Extended_SQLite_Viewer/dbasesingleton.h \
    ../../Extended_SQLite_Viewer/qhexconvertor.h \
    ../../Extended_SQLite_Viewer/qsqlitemodel.h \
    ../../Extended_SQLite_Viewer/qsqlitetablelist.h \
    ../../Extended_SQLite_Viewer/rawdatabaseparserwrapper.h \
    ../../Extended_SQLite_Viewer/rawdatatable.h

unix|win32: LIBS += -L$$PWD/../../Lib/ -lparserlib

INCLUDEPATH += $$PWD/../../parser
DEPENDPATH += $$PWD/../../parser

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../Lib/parserlib.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../Lib/libparserlib.a
