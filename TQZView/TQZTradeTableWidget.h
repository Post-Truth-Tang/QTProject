#ifndef TQZTRADETABLEWIDGET_H
#define TQZTRADETABLEWIDGET_H

#include "ITableWidget.h"

class TQZTradeTableWidget : public ITableWidget
{
    Q_OBJECT
public:
    explicit TQZTradeTableWidget(QWidget *parent = nullptr);

    virtual ~TQZTradeTableWidget();

signals:

};

#endif // TQZTRADETABLEWIDGET_H
