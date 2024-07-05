#include "TQZMainController.h"

#include <QDebug>

#include <QTableWidget>
#include <QLabel>
#include <QFont>

#include "TQZMessageController.h"
#include "TQZView/ITableWidget.h"

TQZMainController::TQZMainController(QWidget *parent):
    IController(parent),
    m_toolItems_view(nullptr),
    m_ban_view(nullptr),
    m_messageController(nullptr),
    m_tradeButtonView(nullptr),
    m_tradeController(nullptr),
    m_orderTableWidget(nullptr),
    m_tradeTableWidget(nullptr),
    m_positionTableWidget(nullptr),
    m_balance_view(nullptr)
{
    this->ResetWindow(0.80, 0.80);
    this->setWindowFlags(Qt::FramelessWindowHint);
}



TQZBalanceView *TQZMainController::balanceView() {
    if (this->m_balance_view == nullptr) {
        this->m_balance_view = new TQZBalanceView(this->banView()->width(), this);

        this->m_balance_view->update(10000, 50, 8000); // for test.
    }

    return this->m_balance_view;
}


void TQZMainController::resizeEvent(QResizeEvent* event)
{
    this->toolItemsView()->move(this->width() - this->toolItemsView()->width(), 0);

    // order table widget.
    this->orderTableWidget()->setFixedSize(this->width() - 3 * this->banView()->x() - this->banView()->width(), (this->height() - 3 * this->banView()->x()) * 0.33);
    this->orderTableWidget()->move(this->banView()->x() + this->banView()->width() + this->banView()->x(), this->banView()->y());

    // trade table widget.
    this->tradeTableWidget()->setFixedSize(this->orderTableWidget()->width(), this->orderTableWidget()->height());
    this->tradeTableWidget()->move(this->orderTableWidget()->x(), this->orderTableWidget()->y() + this->orderTableWidget()->height() + this->banView()->x() * 0.5);

    // position table widget.
    this->positionTableWidget()->setFixedSize(this->orderTableWidget()->width(), this->orderTableWidget()->height());
    this->positionTableWidget()->move(this->orderTableWidget()->x(), this->tradeTableWidget()->y() + this->tradeTableWidget()->height() + this->banView()->x() * 0.5);

    this->tradeButtonView()->move(this->banView()->x(), this->height() - this->tradeButtonView()->height() - this->banView()->x());


    // move balance view;
    this->balanceView()->setFixedWidth(this->banView()->width());

    double diff = this->tradeButtonView()->y() - (this->banView()->y() + this->banView()->height());
    this->balanceView()->move(this->banView()->x(), this->banView()->y() + this->banView()->height() + 0.5 * diff - 0.5 * this->balanceView()->height());

    QMainWindow::resizeEvent(event);
}


TQZOrderTableWidget *TQZMainController::orderTableWidget() {
    if (this->m_orderTableWidget == nullptr) {
        this->m_orderTableWidget = new TQZOrderTableWidget(this);

        void(ITableWidget:: *cellDoubleClicked)(int selectedRow, int selectedColumn) = &ITableWidget::cellDoubleClicked;
        connect(this->m_orderTableWidget, cellDoubleClicked, this, [=](int selectedRow, int selectedColumn){
            qDebug() << "receive this->m_orderTableWidget cellDoubleClicked";

            if (this->m_orderTableWidget->currentRow() < 0)
                return;

        });

    }

    return this->m_orderTableWidget;
}


TQZTradeTableWidget *TQZMainController::tradeTableWidget() {
    if (this->m_tradeTableWidget == nullptr) {
        this->m_tradeTableWidget = new TQZTradeTableWidget(this);

        void(ITableWidget:: *cellDoubleClicked)(int selectedRow, int selectedColumn) = &ITableWidget::cellDoubleClicked;
        connect(this->m_tradeTableWidget, cellDoubleClicked, this, [=](int selectedRow, int selectedColumn){
            qDebug() << "receive this->m_tradeTableWidget cellDoubleClicked";

            if (this->m_tradeTableWidget->currentRow() < 0)
                return;

        });
    }

    return this->m_tradeTableWidget;
}


TQZPositionTableWidget *TQZMainController::positionTableWidget() {
    if (this->m_positionTableWidget == nullptr) {
        this->m_positionTableWidget = new TQZPositionTableWidget(this);

        void(ITableWidget:: *cellDoubleClicked)(int selectedRow, int selectedColumn) = &ITableWidget::cellDoubleClicked;
        connect(this->m_positionTableWidget, cellDoubleClicked, this, [=](int selectedRow, int selectedColumn){
            qDebug() << "receive this->m_positionTableWidget cellDoubleClicked";

            if (this->m_positionTableWidget->currentRow() < 0)
                return;

        });
    }

    return this->m_positionTableWidget;
}


TQZTradeButtonView *TQZMainController::tradeButtonView() {
    if (this->m_tradeButtonView == nullptr) {
        this->m_tradeButtonView = new TQZTradeButtonView(this->banView()->width(), this->banView()->height(), this);
        connect(this->m_tradeButtonView->tradeButton(), &TQZButton::clicked, this, [=](){
            this->tradeController()->show();
        });
    }

    return this->m_tradeButtonView;
}


TQZBanView *TQZMainController::banView() {
    if (this->m_ban_view == nullptr) {
        // TODO: to be continue.
        this->m_ban_view = new TQZBanView(306, this); // new TQZBanView(this->width() * 0.2, this);
        this->m_ban_view->move(this->toolItemsView()->height() * 1.5, this->toolItemsView()->y() + this->toolItemsView()->height() * 1.5);
        this->m_ban_view->accountsComboBox()->addItem("- default -");

        QMap<QString, TQZAccountModel>* accountModels = this->accountModels();
        for (auto iter = accountModels->begin(); iter != accountModels->end(); ++iter) {
            this->m_ban_view->accountsComboBox()->addItem(iter.key());
        }
        this->m_ban_view->accountsComboBox()->setCurrentIndex(0);

        this->m_ban_view->messageButton()->connect(this->m_ban_view->messageButton(), &TQZButton::clicked, this, [=](){
            this->messageController()->show();
        });

        this->m_ban_view->accountsComboBox()->connect(this->m_ban_view->accountsComboBox(), QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
            int previousIndex = this->m_ban_view->accountsComboBox()->property("previousIndex").toInt();

            QString preAccountName = this->m_ban_view->accountsComboBox()->itemText(previousIndex);
            if (preAccountName != "- default -") {
                // preAccountName do log out.
                TQZAccountModel preAccount = accountModels->find(preAccountName).value();
                qDebug() << preAccount.username() << " do log out." << endl;
            }

            QString accountName = this->m_ban_view->accountsComboBox()->itemText(index);
            if (accountName != "- default -") {
                // accountName do log in.
                TQZAccountModel account = accountModels->find(accountName).value();
                qDebug() << account.username() << " do log in." << endl;
            }

            this->m_ban_view->accountsComboBox()->setProperty("previousIndex", index);

            this->m_ban_view->banButton()->click();
        });
        this->m_ban_view->accountsComboBox()->setProperty("previousIndex", this->m_ban_view->accountsComboBox()->currentIndex());

        this->m_ban_view->banButton()->connect(this->m_ban_view->banButton(), &TQZButton::clicked, this, [=](){
            this->m_ban_view->accountsComboBox()->setEnabled(!this->m_ban_view->accountsComboBox()->isEnabled());
            this->m_ban_view->banButton()->setText((this->m_ban_view->banButton()->text() == "lock") ? "unlock" : "lock");
        });
        this->m_ban_view->banButton()->click(); // click when controller first load.
    }

    return this->m_ban_view;
}


TQZMessageController *TQZMainController::messageController() {
    if (this->m_messageController == nullptr) {
        this->m_messageController = new TQZMessageController();
//        this->m_messageController->tableWidget()->connect(this->m_messageController->tableWidget(), SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onMessageTableWidgetDoubleClicked(int,int)));

        void(QTableWidget:: *cellDoubleClicked)(int selectedRow, int selectedColumn) = &QTableWidget::cellDoubleClicked;
        connect(this->m_messageController->tableWidget(), cellDoubleClicked, this, [=](int selectedRow, int selectedColumn){
            qDebug() << "receive this->m_messageController->tableWidget() cellDoubleClicked";

            if (this->messageController()->tableWidget()->currentRow() < 0)
                return;

            QString text0 = this->messageController()->tableWidget()->item(this->messageController()->tableWidget()->currentRow(), 0)->text();
            QString text1 = this->messageController()->tableWidget()->item(this->messageController()->tableWidget()->currentRow(), 1)->text();
            QString text2 = this->messageController()->tableWidget()->item(this->messageController()->tableWidget()->currentRow(), 2)->text();
            qDebug() << "text0: " << text0 << "  text1: " << text1 << "  text2: " << text2;
        });
    }

    return this->m_messageController;
}

TQZTradeController *TQZMainController::tradeController() {
    if (this->m_tradeController == nullptr) {
        this->m_tradeController = new TQZTradeController();

        void(TQZTradeController:: *sendOrderFunction)(QString) = &TQZTradeController::sendOrder;
        connect(this->m_tradeController, sendOrderFunction, this, [=](QString orderInfo){
            // receive a order obj.
            qDebug() << "main controller receive orderInfo: " << orderInfo;
        });
    }

    return this->m_tradeController;
}


TQZToolItemsView *TQZMainController::toolItemsView() {
    if (this->m_toolItems_view == nullptr) {
        this->m_toolItems_view = new TQZToolItemsView(40, 3, this);
        this->m_toolItems_view->move(this->width() - this->m_toolItems_view->width(), 0);

        this->m_toolItems_view->minButton()->connect(this->m_toolItems_view->minButton(), &TQZButton::clicked, this, [=](){
            this->showMinimized();
        });

        this->m_toolItems_view->normalMaxButton()->connect(this->m_toolItems_view->normalMaxButton(), &TQZButton::clicked, this, [=](){
            isMaximized() ? this->showNormal() : this->showMaximized();
        });
        this->m_toolItems_view->closeButton()->connect(this->m_toolItems_view->closeButton(), &TQZButton::clicked, this, [=](){
            this->messageController()->close();
            this->tradeController()->close();
            this->close();
        });
    }

    return this->m_toolItems_view;
}


TQZMainController::~TQZMainController() {
    if (this->m_messageController != nullptr) {
        delete this->m_messageController;
        this->m_messageController = nullptr;
    }

    if (this->m_tradeController != nullptr) {
        delete this->m_tradeController;
        this->m_tradeController = nullptr;
    }
}
