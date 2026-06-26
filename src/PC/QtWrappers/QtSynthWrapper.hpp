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

public:
    explicit                QtSynthWrapper(Synth &synth, QQmlApplicationEngine &appEngine, QObject *parent = nullptr);

    bool                    eventFilter(QObject *obj, QEvent *event) override;

    QtSynthWrapper          &setGate(bool state);
    Synth                   &getSynth() { return this->synth_; };
    QVariantList            &getAudioModules() { return this->qtAudioModules_; };

signals:
    void                    gateChanged();
    void                    audioModulesChanged();

private slots:
    void                    onAudioModuleCreated(AudioModule *newModule, e_audioModules type);
};
