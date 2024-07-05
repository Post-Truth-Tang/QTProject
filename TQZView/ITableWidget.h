#ifndef ITABLEWIDGET_H
#define ITABLEWIDGET_H

#include <QTableWidget>

class ITableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit ITableWidget(QWidget *parent = nullptr);
    virtual ~ITableWidget();

protected:
    virtual void resizeEvent(QResizeEvent* event);

protected:
    QStringList *m_headerList;

signals:

};

#endif // ITABLEWIDGET_H
