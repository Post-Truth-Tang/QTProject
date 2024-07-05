#ifndef TQZLABEL_H
#define TQZLABEL_H

#include <QLabel>

class TQZLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TQZLabel(const QString &text, QWidget *parent = nullptr);

signals:

};

#endif // TQZLABEL_H
