#ifndef TQZTOOLITEMSVIEW_H
#define TQZTOOLITEMSVIEW_H


#include <QGraphicsView>
#include "TQZButton.h"


class TQZToolItemsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TQZToolItemsView(double height, int itemCount, QWidget *parent = nullptr);

    TQZButton *minButton();
    TQZButton *normalMaxButton();
    TQZButton *closeButton();

private:
    void UpdateSelf();

private:
    int m_itemCount;
    double m_height;

private:
    TQZButton *m_minButton;
    TQZButton *m_normalMaxButton;
    TQZButton *m_closeButton;

signals:

};

#endif // TQZTOOLITEMSVIEW_H
