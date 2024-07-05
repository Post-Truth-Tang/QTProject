#include "TestController.h"

#include <QDebug>

#include "TQZView/TQZButton.h"
#include "TQZView/ITableWidget.h"

#include <QLabel>


TestController::TestController(QWidget *parent) : IController(parent)
{
    this->ResetWindow(0.8, 0.8);
    this->setWindowFlags(Qt::FramelessWindowHint);


    // TODO: to be continue.
    // #. create TQZTradeController.


    // #. 把 TQZMainController 中的 order, trade, position 三个tableView connect方法的部分也封装到各自的控件文件内部去;

    this->initTestButtons();
}



void TestController::initTestButtons() {

    this->m_tradeController = new TQZTradeController();

    QPushButton *showButton = new QPushButton("show", this);
    showButton->move(50, 150);
    showButton->setFixedSize(120, 35);
    showButton->connect(showButton, &QPushButton::clicked, this, [=](){
        this->m_tradeController->show();
    });

    QPushButton *closeButton = new QPushButton("close", this);
    closeButton->move(50, 250);
    closeButton->setFixedSize(120, 35);
    closeButton->connect(closeButton, &QPushButton::clicked, this, [=](){
        // close inner controller.
        this->m_tradeController->close();
    });

    QPushButton *closeSelfButton = new QPushButton("close self", this);
    closeSelfButton->move(50, 350);
    closeSelfButton->setFixedSize(120, 35);
    closeSelfButton->connect(closeSelfButton, &QPushButton::clicked, this, [=](){
        this->m_tradeController->close();
        this->close();
    });

}


//void TestController::onTableDoubleClicked(int selectedRow, int selectedColumn) {
//    if (this->m_messageController->tableWidget()->currentRow() < 0)
//        return;

//    QString text0 = this->m_messageController->tableWidget()->item(this->m_messageController->tableWidget()->currentRow(), 0)->text();
//    QString text1 = this->m_messageController->tableWidget()->item(this->m_messageController->tableWidget()->currentRow(), 1)->text();
//    QString text2 = this->m_messageController->tableWidget()->item(this->m_messageController->tableWidget()->currentRow(), 2)->text();
//    qDebug() << "text0: " << text0 << "  text1: " << text1 << "  text2: " << text2 << endl;
//}




TestController::~TestController() {

}
