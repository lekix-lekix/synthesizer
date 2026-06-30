#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QEvent>
#include <QKeyEvent>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQmlContext>

#include <dsp/dsp.hpp>
#include <QtWrappers.hpp>

#include "../Synth.hpp"

class QtSynthWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList qtAudioModules READ getAudioModules NOTIFY audioModulesChanged);

private:
    Synth                   &synth_;
    QQmlApplicationEngine   &appEngine_;
    QVariantList            qtAudioModules_;

    void                    insertQmlModule(QString moduleUrl, QObject *moduleWrapper);

public:
    explicit                QtSynthWrapper(Synth &synth, QQmlApplicationEngine &appEngine, QObject *parent = nullptr);

    bool                    eventFilter(QObject *obj, QEvent *event) override;

    enum class e_audioModulesQt { VCO, VCA, ENV, MIXER_4 };
    Q_ENUM(e_audioModulesQt);

    Synth                   &getSynth() { return synth_; };
    QVariantList            &getAudioModules() { return qtAudioModules_; };
    QtSynthWrapper          &setGate(bool state); // to move in keyboard module

    Q_INVOKABLE void        addAudioModule(e_audioModulesQt type) { synth_.addAudioModule(static_cast<e_audioModules>(type)); };

signals:
    void                    gateChanged();
    void                    audioModulesChanged();

private slots:
    void                    onAudioModuleCreated(AudioModule *newModule, e_audioModules type);
    void                    onConnectionRequest(float &from, float &to) { synth_.connect(from, to); };
};
