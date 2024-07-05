#ifndef TQZBANVIEW_H
#define TQZBANVIEW_H

#include <QWidget>
#include <QGraphicsView>

#include "TQZButton.h"
#include <QComboBox>


class TQZBanView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TQZBanView(double width, QWidget *parent = nullptr);

    TQZButton *banButton();
    QComboBox *accountsComboBox();
    TQZButton *messageButton();

private:
    TQZButton *m_banButton;
    QComboBox *m_accountsComboBox;
    TQZButton *m_messageButton;

    double m_inner_widget_height;
    double m_width;
    double m_height;

signals:

};

#endif // TQZBANVIEW_H
