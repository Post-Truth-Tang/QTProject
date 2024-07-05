#ifndef TQZORDERTABLEWIDGET_H
#define TQZORDERTABLEWIDGET_H


#include "ITableWidget.h"

class TQZOrderTableWidget : public ITableWidget
{
    Q_OBJECT
public:
    explicit TQZOrderTableWidget(QWidget *parent = nullptr);

    virtual ~TQZOrderTableWidget();


signals:

};

#endif // TQZORDERTABLEWIDGET_H
