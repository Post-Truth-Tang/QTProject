#ifndef TQZTRADECONTROLLER_H
#define TQZTRADECONTROLLER_H

#include "IController.h"

#include "TQZView/TQZButton.h"
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>

class TQZTradeController : public IController
{
    Q_OBJECT
public:
    explicit TQZTradeController(QWidget *parent = nullptr);


public:
    TQZButton *sendOrderButton();
    TQZButton *closeButton();
    void updateTick(QObject tick);

private:
    void initAskBidLabels(double x, double y, double width, double labelHeight);
    void initAskBidValueLabels(double x, double y, double width, double labelHeight);

    void initSendOrderUI(double x, double y, double askBidLableWidth, double labelHeight, double edge);
    void initSendOrderButton(double emptyArea_X_Start, double emptyArea_X_end, double emptyArea_Y_Start, double emptyArea_Y_end);

    void initSelf(double askBidLableX, double askBidLableY, double emptyArea_X_end, double labelHeight);


private:
    TQZButton *m_closeButton;

    QLabel *m_ask5PriceLabel;
    QLabel *m_ask4PriceLabel;
    QLabel *m_ask3PriceLabel;
    QLabel *m_ask2PriceLabel;
    QLabel *m_ask1PriceLabel;
    QLabel *m_bid5PriceLabel;
    QLabel *m_bid4PriceLabel;
    QLabel *m_bid3PriceLabel;
    QLabel *m_bid2PriceLabel;
    QLabel *m_bid1PriceLabel;

    QLabel *m_ask5SizeLabel;
    QLabel *m_ask4SizeLabel;
    QLabel *m_ask3SizeLabel;
    QLabel *m_ask2SizeLabel;
    QLabel *m_ask1SizeLabel;
    QLabel *m_bid5SizeLabel;
    QLabel *m_bid4SizeLabel;
    QLabel *m_bid3SizeLabel;
    QLabel *m_bid2SizeLabel;
    QLabel *m_bid1SizeLabel;


    QLineEdit *m_instrumentTextEdit;

    QComboBox *m_exchangeComboBox;
    QComboBox *m_directComboBox;
    QComboBox *m_openCloseComboBox;
    QComboBox *m_orderTypeComboBox;
    QLineEdit *m_priceTextEdit;
    QLineEdit *m_sizeTextEdit;

    TQZButton *m_sendOrderButton;

signals:
    void sendOrder(QString orderInfo);

};

#endif // TQZTRADECONTROLLER_H
