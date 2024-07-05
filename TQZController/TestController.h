#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include "IController.h"
#include "TQZView/TQZBanView.h"

#include "TQZMessageController.h"
#include "TQZTradeController.h"
#include <QTableWidget>


class TestController : public IController
{
    Q_OBJECT
public:
    explicit TestController(QWidget *parent = nullptr);
    virtual ~TestController();

private:
    void initTestButtons();

private:
    TQZTradeController *m_tradeController;


signals:


//private slots:
//    void onTableDoubleClicked(int selectedRow, int selectedColumn);

};

#endif // TESTCONTROLLER_H
