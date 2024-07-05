#ifndef TQZPOSITIONTABLEWIDGET_H
#define TQZPOSITIONTABLEWIDGET_H

#include "ITableWidget.h"

class TQZPositionTableWidget : public ITableWidget
{
    Q_OBJECT
public:
    explicit TQZPositionTableWidget(QWidget *parent = nullptr);

    virtual ~TQZPositionTableWidget();

signals:

};

#endif // TQZPOSITIONTABLEWIDGET_H
