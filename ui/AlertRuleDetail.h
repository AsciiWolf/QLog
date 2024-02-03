#ifndef QLOG_UI_ALERTRULEDETAIL_H
#define QLOG_UI_ALERTRULEDETAIL_H

#include <QDialog>
#include <QCheckBox>

#include "core/AlertEvaluator.h"

namespace Ui {
class AlertRuleDetail;
}

class AlertRuleDetail : public QDialog
{
    Q_OBJECT

public:
    explicit AlertRuleDetail(const QString &ruleName, QWidget *parent);
    ~AlertRuleDetail();

public slots:
    void save();
    void ruleNameChanged(const QString&);
    void callsignChanged(const QString&);
    void spotCommentChanged(const QString&);

private:
    Ui::AlertRuleDetail *ui;
    QString ruleName;
    QStringList ruleNamesList;
    QList<QCheckBox*> memberListCheckBoxes;


private:
    bool ruleExists(const QString &ruleName);
    void loadRule(const QString &ruleName);
    void generateMembershipCheckboxes(const AlertRule * rule = nullptr);
};

#endif // QLOG_UI_ALERTRULEDETAIL_H
