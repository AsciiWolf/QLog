﻿#ifndef RIG_DRIVERS_HAMLIBDRV_H
#define RIG_DRIVERS_HAMLIBDRV_H

#include <QObject>
#include <QTimer>
#include <hamlib/rig.h>

#include "GenericDrv.h"
#include "rig/RigCaps.h"

class HamlibDrv : public GenericDrv
{
public:
    static QList<QPair<int, QString>> getModelList();
    static RigCaps getCaps(int model);
    explicit HamlibDrv(const RigProfile &profile,
                          QObject *parent = nullptr);
    virtual ~HamlibDrv();

    virtual bool open() override;
    virtual bool isMorseOverCatSupported() override;
    virtual QStringList getAvailableModes() override;

    virtual void setFrequency(double) override;
    virtual void setRawMode(const QString &) override;
    virtual void setMode(const QString &, const QString &) override;
    virtual void setPTT(bool) override;
    virtual void setKeySpeed(qint16 wpm) override;
    virtual void syncKeySpeed(qint16 wpm) override;
    virtual void sendMorse(const QString &) override;
    virtual void stopMorse() override;
    virtual void sendState() override;
    virtual void stopTimers() override;

private slots:
    void checkRigStateChange();

private:
    static int addRig(const struct rig_caps* caps, void* data);
    void checkPTTChange();
    bool checkFreqChange();
    bool checkModeChange();
    void checkVFOChange();
    void checkPWRChange();
    void checkRITChange();
    void checkXITChange();
    void checkKeySpeedChange();
    void checkChanges();

    double getRITFreq();
    void setRITFreq(double);
    double getXITFreq();
    void setXITFreq(double);

    void __setKeySpeed(qint16 wpm);
    void __setMode(rmode_t newModeID);
    void commandSleep();

    const QString getModeNormalizedText(const rmode_t mode,
                                        QString &submode) const;
    const QString hamlibMode2String(const rmode_t mode) const;
    const QString hamlibVFO2String(const vfo_t vfo) const;
    serial_handshake_e stringToHamlibFlowControl(const QString &in_flowcontrol);
    serial_parity_e stringToHamlibParity(const QString &in_parity);
    QString hamlibErrorString(int);

    RIG* rig;
    QTimer timer;

    bool forceSendState;
    bool currPTT;
    double currFreq;
    pbwidth_t currPBWidth;
    rmode_t currModeId;
    vfo_t currVFO;
    unsigned int currPWR;
    double currRIT;
    double currXIT;
    unsigned int keySpeed;
    bool morseOverCatSupported;
    QMutex drvLock;

};

#endif // RIG_DRIVERS_HAMLIBDRV_H
