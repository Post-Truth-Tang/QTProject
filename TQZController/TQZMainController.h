#ifndef TQZMAINCONTROLLER_H
#define TQZMAINCONTROLLER_H

#include "IController.h"
#include "TQZView/TQZToolItemsView.h"
#include "TQZView/TQZBanView.h"
#include "TQZView/TQZTradeButtonView.h"
#include "TQZView/TQZBalanceView.h"

#include "TQZMessageController.h"
#include "TQZTradeController.h"

#include "TQZView/TQZOrderTableWidget.h"
#include "TQZView/TQZTradeTableWidget.h"
#include "TQZView/TQZPositionTableWidget.h"

class TQZMainController : public IController
{
    Q_OBJECT
public:
    explicit TQZMainController(QWidget *parent = nullptr);
    virtual ~TQZMainController();

protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    void initBanAccountsView();

    TQZBanView *banView();

    TQZToolItemsView *toolItemsView();
    TQZMessageController *messageController();
    TQZTradeButtonView *tradeButtonView();
    TQZTradeController *tradeController();

    TQZOrderTableWidget *orderTableWidget();
    TQZTradeTableWidget *tradeTableWidget();
    TQZPositionTableWidget *positionTableWidget();

    TQZBalanceView *balanceView();


private:
    TQZToolItemsView *m_toolItems_view;

    TQZBanView *m_ban_view;
    TQZMessageController *m_messageController;

    TQZTradeButtonView *m_tradeButtonView;
    TQZTradeController *m_tradeController;

    TQZOrderTableWidget *m_orderTableWidget;
    TQZTradeTableWidget *m_tradeTableWidget;
    TQZPositionTableWidget *m_positionTableWidget;

    TQZBalanceView *m_balance_view;


signals:


};

#endif // TQZMAINCONTROLLER_H
