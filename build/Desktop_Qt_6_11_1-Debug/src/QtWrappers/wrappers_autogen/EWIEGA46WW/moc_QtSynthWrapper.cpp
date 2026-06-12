/****************************************************************************
** Meta object code from reading C++ file 'QtSynthWrapper.hpp'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/QtWrappers/QtSynthWrapper.hpp"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QtSynthWrapper.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN14QtSynthWrapperE_t {};
} // unnamed namespace

template <> constexpr inline auto QtSynthWrapper::qt_create_metaobjectdata<qt_meta_tag_ZN14QtSynthWrapperE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "QtSynthWrapper",
        "gateChanged",
        "",
        "audioModulesChanged",
        "modulatorsChanged",
        "onModulatorCreated",
        "Modulator*",
        "newModule",
        "e_modulators",
        "type",
        "onAudioModuleCreated",
        "AudioModule*",
        "e_audioModules",
        "qtAudioModules",
        "QVariantList",
        "qtModulators"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'gateChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'audioModulesChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'modulatorsChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onModulatorCreated'
        QtMocHelpers::SlotData<void(Modulator *, e_modulators)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 6, 7 }, { 0x80000000 | 8, 9 },
        }}),
        // Slot 'onAudioModuleCreated'
        QtMocHelpers::SlotData<void(AudioModule *, e_audioModules)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 11, 7 }, { 0x80000000 | 12, 9 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'qtAudioModules'
        QtMocHelpers::PropertyData<QVariantList>(13, 0x80000000 | 14, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 1),
        // property 'qtModulators'
        QtMocHelpers::PropertyData<QVariantList>(15, 0x80000000 | 14, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<QtSynthWrapper, qt_meta_tag_ZN14QtSynthWrapperE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject QtSynthWrapper::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14QtSynthWrapperE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14QtSynthWrapperE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN14QtSynthWrapperE_t>.metaTypes,
    nullptr
} };

void QtSynthWrapper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<QtSynthWrapper *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->gateChanged(); break;
        case 1: _t->audioModulesChanged(); break;
        case 2: _t->modulatorsChanged(); break;
        case 3: _t->onModulatorCreated((*reinterpret_cast<std::add_pointer_t<Modulator*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<e_modulators>>(_a[2]))); break;
        case 4: _t->onAudioModuleCreated((*reinterpret_cast<std::add_pointer_t<AudioModule*>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<e_audioModules>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (QtSynthWrapper::*)()>(_a, &QtSynthWrapper::gateChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (QtSynthWrapper::*)()>(_a, &QtSynthWrapper::audioModulesChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (QtSynthWrapper::*)()>(_a, &QtSynthWrapper::modulatorsChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QVariantList*>(_v) = _t->getAudioModules(); break;
        case 1: *reinterpret_cast<QVariantList*>(_v) = _t->getModulators(); break;
        default: break;
        }
    }
}

const QMetaObject *QtSynthWrapper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtSynthWrapper::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN14QtSynthWrapperE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QtSynthWrapper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QtSynthWrapper::gateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QtSynthWrapper::audioModulesChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void QtSynthWrapper::modulatorsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
