#include "TQZBalanceView.h"

#include <QDebug>

TQZBalanceView::TQZBalanceView(double width, QWidget *parent):
    QGraphicsView(parent),
    m_width(width),
    m_accountIdLabel(nullptr),
    m_accountIdValueLabel(nullptr),
    m_balanceLabel(nullptr),
    m_balanceValueLabel(nullptr),
    m_frozenLabel(nullptr),
    m_frozenValueLabel(nullptr),
    m_availableLabel(nullptr),
    m_availableValueLabel(nullptr),
    m_riskPctLabel(nullptr),
    m_riskPctValueLabel(nullptr),
    m_interfaceLabel(nullptr),
    m_interfaceValueLabel(nullptr)
{
    this->setStyleSheet("background: transparent");

    int edge = 5;
    double lableHeight = 30;
    this->setFixedHeight(lableHeight * 6 + edge * 5);

    // account id
    this->accountIdLabel()->move(0, 0);
    this->accountIdLabel()->setFixedSize(120, lableHeight);

    this->accountIdValueLabel()->move(this->accountIdLabel()->x() + this->accountIdLabel()->width() + edge, this->accountIdLabel()->y());
    this->accountIdValueLabel()->setFixedSize(this->m_width - this->accountIdLabel()->width() - edge, this->accountIdLabel()->height());


    // balance label
    this->balanceLabel()->move(this->accountIdLabel()->x(), this->accountIdLabel()->y() + this->accountIdLabel()->height() + edge);
    this->balanceLabel()->setFixedSize(this->accountIdLabel()->width(), this->accountIdLabel()->height());

    this->balanceValueLabel()->move(this->accountIdValueLabel()->x(), this->balanceLabel()->y());
    this->balanceValueLabel()->setFixedSize(this->accountIdValueLabel()->width(), this->accountIdValueLabel()->height());


    // frozen label
    this->frozenLabel()->move(this->balanceLabel()->x(), this->balanceLabel()->y() + this->balanceLabel()->height() + edge);
    this->frozenLabel()->setFixedSize(this->balanceLabel()->width(), this->balanceLabel()->height());

    this->frozenValueLabel()->move(this->accountIdValueLabel()->x(), this->frozenLabel()->y());
    this->frozenValueLabel()->setFixedSize(this->accountIdValueLabel()->width(), this->accountIdValueLabel()->height());


    // available label
    this->availableLabel()->move(this->frozenLabel()->x(), this->frozenLabel()->y() + this->frozenLabel()->height() + edge);
    this->availableLabel()->setFixedSize(this->frozenLabel()->width(), this->frozenLabel()->height());

    this->availableValueLabel()->move(this->accountIdValueLabel()->x(), this->availableLabel()->y());
    this->availableValueLabel()->setFixedSize(this->accountIdValueLabel()->width(), this->accountIdValueLabel()->height());


    // risk_pct label
    this->riskPctLabel()->move(this->availableLabel()->x(), this->availableLabel()->y() + this->availableLabel()->height() + edge);
    this->riskPctLabel()->setFixedSize(this->availableLabel()->width(), this->availableLabel()->height());

    this->riskPctValueLabel()->move(this->accountIdValueLabel()->x(), this->riskPctLabel()->y());
    this->riskPctValueLabel()->setFixedSize(this->accountIdValueLabel()->width(), this->accountIdValueLabel()->height());


    // interface label
    this->interfaceLabel()->move(this->riskPctLabel()->x(), this->riskPctLabel()->y() + this->riskPctLabel()->height() + edge);
    this->interfaceLabel()->setFixedSize(this->riskPctLabel()->width(), this->riskPctLabel()->height());

    this->interfaceValueLabel()->move(this->accountIdValueLabel()->x(), this->interfaceLabel()->y());
    this->interfaceValueLabel()->setFixedSize(this->accountIdValueLabel()->width(), this->accountIdValueLabel()->height());
}


void TQZBalanceView::setAccountId(QString accountId) {
    this->accountIdValueLabel()->setText(accountId);
}
void TQZBalanceView::setInterface(QString interface) {
    this->interfaceValueLabel()->setText(interface);
}

void TQZBalanceView::update(double balance, double frozen, double available) {
    this->balanceValueLabel()->setText(QString::number(balance, 'f', 2));
    this->frozenValueLabel()->setText(QString::number(frozen, 'f', 2));
    this->availableValueLabel()->setText(QString::number(available, 'f', 2));

    if (qFuzzyCompare(balance, 0.0)) {
        this->riskPctValueLabel()->setText("0.00%");
    } else {
        this->riskPctValueLabel()->setText(QString::number(100 * (balance - frozen - available) / balance, 'f', 2) + "%");
    }

}



TQZLabel *TQZBalanceView::accountIdLabel() {
    if (this->m_accountIdLabel == nullptr) {
        this->m_accountIdLabel = new TQZLabel("account id : ", this);
        this->m_accountIdLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }

    return this->m_accountIdLabel;
}

TQZLabel *TQZBalanceView::accountIdValueLabel() {
    if (this->m_accountIdValueLabel == nullptr) {
        this->m_accountIdValueLabel = new TQZLabel("175896", this);
        this->m_accountIdValueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    return this->m_accountIdValueLabel;
}


TQZLabel *TQZBalanceView::balanceLabel() {
    if (this->m_balanceLabel == nullptr) {
        this->m_balanceLabel = new TQZLabel("balance : ", this);
        this->m_balanceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }

    return this->m_balanceLabel;
}
TQZLabel *TQZBalanceView::balanceValueLabel() {
    if (this->m_balanceValueLabel == nullptr) {
        double balanceValue = 10000000000.141;
        this->m_balanceValueLabel = new TQZLabel(QString::number(balanceValue, 'f', 2), this);
        this->m_balanceValueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    return this->m_balanceValueLabel;
}

TQZLabel *TQZBalanceView::frozenLabel() {
    if (this->m_frozenLabel == nullptr) {
        this->m_frozenLabel = new TQZLabel("frozen : ", this);
        this->m_frozenLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }

    return this->m_frozenLabel;
}
TQZLabel *TQZBalanceView::frozenValueLabel() {
    if (this->m_frozenValueLabel == nullptr) {
        this->m_frozenValueLabel = new TQZLabel("3.1415", this);
        this->m_frozenValueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    return this->m_frozenValueLabel;
}

TQZLabel *TQZBalanceView::availableLabel() {
    if (this->m_availableLabel == nullptr) {
        this->m_availableLabel = new TQZLabel("available : ", this);
        this->m_availableLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }

    return this->m_availableLabel;
}
TQZLabel *TQZBalanceView::availableValueLabel() {
    if (this->m_availableValueLabel == nullptr) {
        this->m_availableValueLabel = new TQZLabel("3.14159", this);
        this->m_availableValueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    return this->m_availableValueLabel;
}

TQZLabel *TQZBalanceView::riskPctLabel() {
    if (this->m_riskPctLabel == nullptr) {
        this->m_riskPctLabel = new TQZLabel("risk_pct : ", this);
        this->m_riskPctLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }

    return this->m_riskPctLabel;
}
TQZLabel *TQZBalanceView::riskPctValueLabel() {
    if (this->m_riskPctValueLabel == nullptr) {
        this->m_riskPctValueLabel = new TQZLabel("3.1415926", this);
        this->m_riskPctValueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    return this->m_riskPctValueLabel;
}

TQZLabel *TQZBalanceView::interfaceLabel() {
    if (this->m_interfaceLabel == nullptr) {
        this->m_interfaceLabel = new TQZLabel("interface : ", this);
        this->m_interfaceLabel->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    }

    return this->m_interfaceLabel;
}
TQZLabel *TQZBalanceView::interfaceValueLabel() {
    if (this->m_interfaceValueLabel == nullptr) {
        this->m_interfaceValueLabel = new TQZLabel("CTP", this);
        this->m_interfaceValueLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    return this->m_interfaceValueLabel;
}




TQZBalanceView::~TQZBalanceView() {

}


