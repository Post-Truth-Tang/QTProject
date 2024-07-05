#ifndef TQZBALANCEVIEW_H
#define TQZBALANCEVIEW_H

#include <QGraphicsView>
#include "TQZView/TQZLabel.h"

class TQZBalanceView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TQZBalanceView(double width, QWidget *parent = nullptr);
    virtual ~TQZBalanceView();

public:
    void setAccountId(QString accountId);
    void setInterface(QString interface);

    void update(double balance, double frozen, double available);


private:
    TQZLabel *accountIdLabel();
    TQZLabel *accountIdValueLabel();

    TQZLabel *balanceLabel();
    TQZLabel *balanceValueLabel();

    TQZLabel *frozenLabel();
    TQZLabel *frozenValueLabel();

    TQZLabel *availableLabel();
    TQZLabel *availableValueLabel();

    TQZLabel *riskPctLabel();
    TQZLabel *riskPctValueLabel();

    TQZLabel *interfaceLabel();
    TQZLabel *interfaceValueLabel();


private:
    double m_width;

    TQZLabel *m_accountIdLabel;
    TQZLabel *m_accountIdValueLabel;

    TQZLabel *m_balanceLabel;
    TQZLabel *m_balanceValueLabel;

    TQZLabel *m_frozenLabel;
    TQZLabel *m_frozenValueLabel;

    TQZLabel *m_availableLabel;
    TQZLabel *m_availableValueLabel;

    TQZLabel *m_riskPctLabel;
    TQZLabel *m_riskPctValueLabel;

    TQZLabel *m_interfaceLabel;
    TQZLabel *m_interfaceValueLabel;


signals:

};

#endif // TQZBALANCEVIEW_H
