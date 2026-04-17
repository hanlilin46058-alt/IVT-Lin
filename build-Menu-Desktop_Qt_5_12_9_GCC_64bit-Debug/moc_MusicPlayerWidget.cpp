/****************************************************************************
** Meta object code from reading C++ file 'MusicPlayerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Menu/MusicPlayerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MusicPlayerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MusicPlayerWidget_t {
    QByteArrayData data[18];
    char stringdata0[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlayerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlayerWidget_t qt_meta_stringdata_MusicPlayerWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MusicPlayerWidget"
QT_MOC_LITERAL(1, 18, 16), // "btn_play_clicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "btn_next_clicked"
QT_MOC_LITERAL(4, 53, 20), // "btn_previous_clicked"
QT_MOC_LITERAL(5, 74, 23), // "mediaPlayerStateChanged"
QT_MOC_LITERAL(6, 98, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(7, 118, 5), // "state"
QT_MOC_LITERAL(8, 124, 16), // "listWidgetCliked"
QT_MOC_LITERAL(9, 141, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(10, 158, 4), // "item"
QT_MOC_LITERAL(11, 163, 32), // "mediaPlaylistCurrentIndexChanged"
QT_MOC_LITERAL(12, 196, 5), // "index"
QT_MOC_LITERAL(13, 202, 26), // "musicPlayerDurationChanged"
QT_MOC_LITERAL(14, 229, 8), // "duration"
QT_MOC_LITERAL(15, 238, 26), // "mediaPlayerPositionChanged"
QT_MOC_LITERAL(16, 265, 8), // "position"
QT_MOC_LITERAL(17, 274, 22) // "durationSliderReleased"

    },
    "MusicPlayerWidget\0btn_play_clicked\0\0"
    "btn_next_clicked\0btn_previous_clicked\0"
    "mediaPlayerStateChanged\0QMediaPlayer::State\0"
    "state\0listWidgetCliked\0QListWidgetItem*\0"
    "item\0mediaPlaylistCurrentIndexChanged\0"
    "index\0musicPlayerDurationChanged\0"
    "duration\0mediaPlayerPositionChanged\0"
    "position\0durationSliderReleased"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlayerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
      11,    1,   68,    2, 0x08 /* Private */,
      13,    1,   71,    2, 0x08 /* Private */,
      15,    1,   74,    2, 0x08 /* Private */,
      17,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::LongLong,   14,
    QMetaType::Void, QMetaType::LongLong,   16,
    QMetaType::Void,

       0        // eod
};

void MusicPlayerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicPlayerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->btn_play_clicked(); break;
        case 1: _t->btn_next_clicked(); break;
        case 2: _t->btn_previous_clicked(); break;
        case 3: _t->mediaPlayerStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 4: _t->listWidgetCliked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->mediaPlaylistCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->musicPlayerDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->mediaPlayerPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->durationSliderReleased(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MusicPlayerWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_MusicPlayerWidget.data,
    qt_meta_data_MusicPlayerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MusicPlayerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MusicPlayerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MusicPlayerWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MusicPlayerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
