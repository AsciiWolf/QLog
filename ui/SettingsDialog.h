#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlTableModel>
#include <QCompleter>
#include <hamlib/rig.h>

#include "data/StationProfile.h"
#include "data/RigProfile.h"
#include "data/RotProfile.h"
#include "data/AntProfile.h"
#include "data/CWKeyProfile.h"
#include "data/CWShortcutProfile.h"

namespace Ui {
class SettingsDialog;
}

class QSqlTableModel;

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

public slots:
    void save();

    void addRigProfile();
    void delRigProfile();
    void refreshRigProfilesView();
    void doubleClickRigProfile(QModelIndex);
    void clearRigProfileForm();
    void rigRXOffsetChanged(int);
    void rigTXOffsetChanged(int);
    void rigGetFreqChanged(int);

    void addRotProfile();
    void delRotProfile();
    void refreshRotProfilesView();
    void doubleClickRotProfile(QModelIndex);
    void clearRotProfileForm();

    void addAntProfile();
    void delAntProfile();
    void refreshAntProfilesView();
    void doubleClickAntProfile(QModelIndex);
    void clearAntProfileForm();

    void addCWKeyProfile();
    void delCWKeyProfile();
    void refreshCWKeyProfilesView();
    void doubleClickCWKeyProfile(QModelIndex);
    void clearCWKeyProfileForm();

    void addCWShortcutProfile();
    void delCWShortcutProfile();
    void refreshCWShortcutProfilesView();
    void doubleClickCWShortcutProfile(QModelIndex);
    void clearCWShortcutProfileForm();

    void refreshStationProfilesView();
    void addStationProfile();
    void deleteStationProfile();
    void doubleClickStationProfile(QModelIndex);
    void clearStationProfileForm();

    void rigChanged(int);
    void rotChanged(int);
    void cwKeyChanged(int);
    void tqslPathBrowse();
    void adjustCallsignTextColor();
    void adjustLocatorTextColor();
    void adjustVUCCLocatorTextColor();
    void eqslDirBrowse();
    void paperDirBrowse();
    void cancelled();
    void sotaChanged(QString);
    void primaryCallbookChanged(int);
    void secondaryCallbookChanged(int);

private:
    void readSettings();
    void writeSettings();
    void setUIBasedOnRigCaps(const struct rig_caps *caps);
    void refreshRigAssignedCWKeyCombo();

    QSqlTableModel* modeTableModel;
    QSqlTableModel* bandTableModel;
    StationProfilesManager *stationProfManager;
    RigProfilesManager *rigProfManager;
    RotProfilesManager *rotProfManager;
    AntProfilesManager *antProfManager;
    CWKeyProfilesManager *cwKeyProfManager;
    CWShortcutProfilesManager *cwShortcutProfManager;
    QCompleter *sotaCompleter;
    QCompleter *iotaCompleter;
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
