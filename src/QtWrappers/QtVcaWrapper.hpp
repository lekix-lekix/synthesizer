#pragma once

#include <QObject>

#include <dsp_library/dsp.hpp>
#include <QtWrappers.hpp>

class QtVcaWrapper : public QtModuleWrapper
{
    Q_OBJECT
    Q_PROPERTY(float gain READ getGain WRITE setGain NOTIFY gainChanged);

private:
    Vca *vca_;

public:
    explicit        QtVcaWrapper(Vca *vca, QObject *parent = nullptr);

    float           getGain() { return vca_->getGain(); };
    QtVcaWrapper    &setGain(float newVal) { vca_->setGain(newVal); return *this; };

signals:
    void            gainChanged();
};
