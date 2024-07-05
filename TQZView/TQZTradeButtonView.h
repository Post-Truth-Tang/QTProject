#ifndef TQZTRADEBUTTONVIEW_H
#define TQZTRADEBUTTONVIEW_H


#include <QGraphicsView>
#include "TQZView/TQZButton.h"


class TQZTradeButtonView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TQZTradeButtonView(double width, double buttonHeight, QWidget *parent = nullptr);

public:
    TQZButton *tradeButton();
    TQZButton *cancelAllButton();


private:
    TQZButton *m_tradeButton;
    TQZButton *m_cancelAllButton;
    double m_width;
    double m_buttonHeight;


signals:

};

#endif // TQZTRADEBUTTONVIEW_H
