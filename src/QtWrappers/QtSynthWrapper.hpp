#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariant>
#include <QEvent>
#include <QKeyEvent>

#include <memory>

#include "Synth.hpp"
#include "QtEnvWrapper.hpp"
#include "QtOscWrapper.hpp"

class QtSynthWrapper : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList qtAudioModules READ getAudioModules NOTIFY audioModulesChanged);
    Q_PROPERTY(QVariantList qtModulators READ getModulators NOTIFY modulatorsChanged);

public:
    explicit QtSynthWrapper(Synth &synth, QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;

    QtSynthWrapper      &setGate(bool state);
    Synth               &getSynth() { return this->synth_; };
    QVariantList        &getAudioModules() { return this->qtAudioModules_; };
    QVariantList        &getModulators() { return this->qtModulators_; };

signals:
    void gateChanged();
    void audioModulesChanged();
    void modulatorsChanged();

private:
    Synth &synth_;
    QVariantList qtAudioModules_;
    QVariantList qtModulators_;

private slots:
    void onModulatorCreated(Modulator *newModule, e_modulators type);
    void onAudioModuleCreated(AudioModule *newModule, e_audioModules type);
};
