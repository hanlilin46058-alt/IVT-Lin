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
    QByteArrayData data[19];
    char stringdata0[310];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MusicPlayerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MusicPlayerWidget_t qt_meta_stringdata_MusicPlayerWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "MusicPlayerWidget"
QT_MOC_LITERAL(1, 18, 12), // "returnToMain"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 16), // "btn_play_clicked"
QT_MOC_LITERAL(4, 49, 16), // "btn_next_clicked"
QT_MOC_LITERAL(5, 66, 20), // "btn_previous_clicked"
QT_MOC_LITERAL(6, 87, 23), // "mediaPlayerStateChanged"
QT_MOC_LITERAL(7, 111, 19), // "QMediaPlayer::State"
QT_MOC_LITERAL(8, 131, 5), // "state"
QT_MOC_LITERAL(9, 137, 16), // "listWidgetCliked"
QT_MOC_LITERAL(10, 154, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(11, 171, 4), // "item"
QT_MOC_LITERAL(12, 176, 32), // "mediaPlaylistCurrentIndexChanged"
QT_MOC_LITERAL(13, 209, 5), // "index"
QT_MOC_LITERAL(14, 215, 26), // "musicPlayerDurationChanged"
QT_MOC_LITERAL(15, 242, 8), // "duration"
QT_MOC_LITERAL(16, 251, 26), // "mediaPlayerPositionChanged"
QT_MOC_LITERAL(17, 278, 8), // "position"
QT_MOC_LITERAL(18, 287, 22) // "durationSliderReleased"

    },
    "MusicPlayerWidget\0returnToMain\0\0"
    "btn_play_clicked\0btn_next_clicked\0"
    "btn_previous_clicked\0mediaPlayerStateChanged\0"
    "QMediaPlayer::State\0state\0listWidgetCliked\0"
    "QListWidgetItem*\0item\0"
    "mediaPlaylistCurrentIndexChanged\0index\0"
    "musicPlayerDurationChanged\0duration\0"
    "mediaPlayerPositionChanged\0position\0"
    "durationSliderReleased"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MusicPlayerWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    1,   68,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      12,    1,   74,    2, 0x08 /* Private */,
      14,    1,   77,    2, 0x08 /* Private */,
      16,    1,   80,    2, 0x08 /* Private */,
      18,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::LongLong,   15,
    QMetaType::Void, QMetaType::LongLong,   17,
    QMetaType::Void,

       0        // eod
};

void MusicPlayerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MusicPlayerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnToMain(); break;
        case 1: _t->btn_play_clicked(); break;
        case 2: _t->btn_next_clicked(); break;
        case 3: _t->btn_previous_clicked(); break;
        case 4: _t->mediaPlayerStateChanged((*reinterpret_cast< QMediaPlayer::State(*)>(_a[1]))); break;
        case 5: _t->listWidgetCliked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->mediaPlaylistCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->musicPlayerDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 8: _t->mediaPlayerPositionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 9: _t->durationSliderReleased(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::State >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MusicPlayerWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MusicPlayerWidget::returnToMain)) {
                *result = 0;
                return;
            }
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MusicPlayerWidget::returnToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
