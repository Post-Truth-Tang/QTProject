#ifndef TQZMESSAGECONTROLLER_H
#define TQZMESSAGECONTROLLER_H

#include "IController.h"

#include <QTableWidget>
#include "TQZView/TQZButton.h"

class TQZMessageController : public IController
{
    Q_OBJECT
public:
    explicit TQZMessageController(QWidget *parent = nullptr);

public:
    QTableWidget *tableWidget();
    void insertMessage(QString timeText, QString messageText, QString interfaceText);

    void clear();

protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    TQZButton *closeButton();

private:
    QTableWidget *m_tableWidget;
    TQZButton *m_closeButton;

signals:

};

#endif // TQZMESSAGECONTROLLER_H
