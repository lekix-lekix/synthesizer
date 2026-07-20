#pragma once

#include <QObject>
#include <QJSEngine>
#include <unordered_map>
#include <Synth.hpp>
#include <QKeyEvent>
#include <qqml.h>

constexpr int SHIFT = 16777248;

class InputHandler : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

private:
    Synth                               &synth_;
    std::unordered_map<QString, bool>   inputs_;
    inline static InputHandler *s_instance = nullptr;

    void                                initInputs();

public:
    InputHandler(Synth &synth, QObject *parent = nullptr) : synth_(synth), QObject(parent) { initInputs(); };

    bool                    eventFilter(QObject *obj, QEvent *event) override;

    Q_INVOKABLE bool        getInput(QString input) { return inputs_[input]; }

    Q_INVOKABLE void        print() { std::cout << "coucou" << std::endl;};

        // Called by QML engine instead of a constructor
    static InputHandler *create(QQmlEngine *, QJSEngine *engine) {
        Q_ASSERT(s_instance); // must be set before QML tries to access itx`
        QJSEngine::setObjectOwnership(s_instance, QJSEngine::CppOwnership);
        return s_instance;
    }

    // Call this once from main(), before the QML engine loads anything
    static void setInstance(InputHandler *instance) {
        s_instance = instance;
    }


signals:
};