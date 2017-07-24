/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[20];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 18), // "on_connect_clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "on_stop_clicked"
QT_MOC_LITERAL(4, 43, 17), // "on_record_clicked"
QT_MOC_LITERAL(5, 61, 21), // "on_stoprecord_clicked"
QT_MOC_LITERAL(6, 83, 11), // "sendrequest"
QT_MOC_LITERAL(7, 95, 4), // "read"
QT_MOC_LITERAL(8, 100, 11), // "socketerror"
QT_MOC_LITERAL(9, 112, 5), // "doRun"
QT_MOC_LITERAL(10, 118, 6), // "doBack"
QT_MOC_LITERAL(11, 125, 6), // "doLeft"
QT_MOC_LITERAL(12, 132, 7), // "doRight"
QT_MOC_LITERAL(13, 140, 9), // "doStopCar"
QT_MOC_LITERAL(14, 150, 8), // "doBuzzer"
QT_MOC_LITERAL(15, 159, 6), // "doHelp"
QT_MOC_LITERAL(16, 166, 7), // "doSpeed"
QT_MOC_LITERAL(17, 174, 9), // "doRefresh"
QT_MOC_LITERAL(18, 184, 6), // "read_t"
QT_MOC_LITERAL(19, 191, 13) // "readFrameRate"

    },
    "Widget\0on_connect_clicked\0\0on_stop_clicked\0"
    "on_record_clicked\0on_stoprecord_clicked\0"
    "sendrequest\0read\0socketerror\0doRun\0"
    "doBack\0doLeft\0doRight\0doStopCar\0"
    "doBuzzer\0doHelp\0doSpeed\0doRefresh\0"
    "read_t\0readFrameRate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x08 /* Private */,
       3,    0,  105,    2, 0x08 /* Private */,
       4,    0,  106,    2, 0x08 /* Private */,
       5,    0,  107,    2, 0x08 /* Private */,
       6,    0,  108,    2, 0x08 /* Private */,
       7,    0,  109,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    0,  113,    2, 0x08 /* Private */,
      12,    0,  114,    2, 0x08 /* Private */,
      13,    0,  115,    2, 0x08 /* Private */,
      14,    0,  116,    2, 0x08 /* Private */,
      15,    0,  117,    2, 0x08 /* Private */,
      16,    0,  118,    2, 0x08 /* Private */,
      17,    0,  119,    2, 0x08 /* Private */,
      18,    0,  120,    2, 0x08 /* Private */,
      19,    0,  121,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_connect_clicked(); break;
        case 1: _t->on_stop_clicked(); break;
        case 2: _t->on_record_clicked(); break;
        case 3: _t->on_stoprecord_clicked(); break;
        case 4: _t->sendrequest(); break;
        case 5: _t->read(); break;
        case 6: _t->socketerror(); break;
        case 7: _t->doRun(); break;
        case 8: _t->doBack(); break;
        case 9: _t->doLeft(); break;
        case 10: _t->doRight(); break;
        case 11: _t->doStopCar(); break;
        case 12: _t->doBuzzer(); break;
        case 13: _t->doHelp(); break;
        case 14: _t->doSpeed(); break;
        case 15: _t->doRefresh(); break;
        case 16: _t->read_t(); break;
        case 17: _t->readFrameRate(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(const_cast< Widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
