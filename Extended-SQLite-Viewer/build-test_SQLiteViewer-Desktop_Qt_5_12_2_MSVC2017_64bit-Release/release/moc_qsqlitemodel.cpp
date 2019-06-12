/****************************************************************************
** Meta object code from reading C++ file 'qsqlitemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Extended_SQLite_Viewer/qsqlitemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qsqlitemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QSQLiteModel_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QSQLiteModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QSQLiteModel_t qt_meta_stringdata_QSQLiteModel = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QSQLiteModel"
QT_MOC_LITERAL(1, 13, 19), // "tableNameWasChanged"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "removeRow"
QT_MOC_LITERAL(4, 44, 3), // "row"
QT_MOC_LITERAL(5, 48, 11), // "setDataBase"
QT_MOC_LITERAL(6, 60, 9) // "tableName"

    },
    "QSQLiteModel\0tableNameWasChanged\0\0"
    "removeRow\0row\0setDataBase\0tableName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QSQLiteModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x02 /* Public */,
       5,    1,   33,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Int, QMetaType::QString,    6,

       0        // eod
};

void QSQLiteModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QSQLiteModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->tableNameWasChanged(); break;
        case 1: _t->removeRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: { int _r = _t->setDataBase((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QSQLiteModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QSQLiteModel::tableNameWasChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QSQLiteModel::staticMetaObject = { {
    &QSqlTableModel::staticMetaObject,
    qt_meta_stringdata_QSQLiteModel.data,
    qt_meta_data_QSQLiteModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QSQLiteModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QSQLiteModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QSQLiteModel.stringdata0))
        return static_cast<void*>(this);
    return QSqlTableModel::qt_metacast(_clname);
}

int QSQLiteModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QSQLiteModel::tableNameWasChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
