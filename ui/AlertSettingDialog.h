#ifndef QLOG_UI_ALERTSETTINGDIALOG_H
#define QLOG_UI_ALERTSETTINGDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class AlertSettingDialog;
}

class AlertSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlertSettingDialog(QWidget *parent = nullptr);
    ~AlertSettingDialog();

private:
    Ui::AlertSettingDialog *ui;
    QSqlTableModel* rulesModel;

public slots:
    void addRule();
    void removeRule();
    void editRule(QModelIndex);
    void editRuleButton();

};

#endif // QLOG_UI_ALERTSETTINGDIALOG_H
