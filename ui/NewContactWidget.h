#ifndef NEWCONTACTWIDGET_H
#define NEWCONTACTWIDGET_H

#include <QWidget>
#include <QSqlRecord>
#include <QCompleter>
#include "core/Cty.h"
#include "data/Data.h"
#include "core/Conditions.h"
#include "core/Gridsquare.h"
#include "data/DxSpot.h"
#include "core/Rig.h"
#include "core/CallbookManager.h"

namespace Ui {
class NewContactWidget;
}

enum CoordPrecision {
    COORD_NONE = 0,
    COORD_DXCC = 1,
    COORD_GRID = 2,
    COORD_FULL = 3
};

class NewContactWidget : public QWidget {
    Q_OBJECT

public:
    explicit NewContactWidget(QWidget *parent = nullptr);
    ~NewContactWidget();

    void addPropConditions(Conditions *);

signals:
    void contactAdded(QSqlRecord record);
    void newTarget(double lat, double lon);
    void filterCallsign(QString call);
    void userFrequencyChanged(VFOID, double, double, double);
    void markQSO(DxSpot spot);

    void stationProfileChanged();
    void rigProfileChanged();
    void antProfileChanged();

public slots:
    void refreshRigProfileCombo();
    void saveExternalContact(QSqlRecord record);
    void readGlobalSettings();
    void tuneDx(QString callsign, double frequency);
    void showDx(QString callsign, QString grid);
    void resetContact();
    void saveContact();

    // to receive RIG instructions
    void changeFrequency(VFOID, double, double, double);
    void changeMode(VFOID, QString rawMode, QString mode, QString subMode);
    void changePower(VFOID, double power);
    void rigConnected();
    void rigDisconnected();

private slots:
    void callsignChanged();
    void frequencyTXChanged();
    void frequencyRXChanged();
    void bandChanged();
    void modeChanged();
    void subModeChanged();
    void gridChanged();
    void updateTime();
    void updateTimeOff();
    void startContactTimer();
    void stopContactTimer();
    void markContact();
    void editCallsignFinished();
    void callsignResult(const QMap<QString, QString>& data);
    void propModeChanged(const QString&);
    void sotaChanged(QString);

    void stationProfileComboChanged(QString);
    void rigProfileComboChanged(QString);
    void antProfileComboChanged(QString);
    void qrz();

private:
    void fillFieldsFromLastQSO(QString callsign);
    void queryDxcc(QString callsign);
    void clearQueryFields();
    void readWidgetSettings();
    void writeWidgetSetting();
    void __modeChanged();
    void refreshStationProfileCombo();
    void updateTXBand(double freq);
    void updateRXBand(double freq);
    void updateCoordinates(double lat, double lon, CoordPrecision prec);
    void updateDxccStatus();
    void updatePartnerLocTime();
    void setDefaultReport();
    void refreshAntProfileCombo();
    void addAddlFields(QSqlRecord &record);
    bool eventFilter(QObject *object, QEvent *event);
    bool isQSOTimeStarted();

private:
    Rig* rig;
    double realRigFreq;
    QString callsign;
    DxccEntity dxccEntity;
    QString defaultReport;
    CallbookManager callbookManager;
    QTimer* contactTimer;
    Ui::NewContactWidget *ui;
    CoordPrecision coordPrec;
    Conditions *prop_cond;
    QCompleter *iotaCompleter;
    QCompleter *satCompleter;
    QCompleter *sotaCompleter;
    QTimeZone partnerTimeZone;
};

#endif // NEWCONTACTWIDGET_H
