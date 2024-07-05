#ifndef TQZBUTTON_H
#define TQZBUTTON_H

#include <QPushButton>

enum TQZButtonType {
    COMMON,
    CLOSE,
    LOCK,
    MESSAGE,
    CANCEL
};

class TQZButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TQZButton(const QString &text, TQZButtonType buttonType , QWidget *parent = nullptr);
    virtual ~TQZButton();

protected:
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:
    enum TQZButtonStyleType {
        DEFAULT,
        MOVEIN
    };


private:
    void UpdateSelf(const QString &text);
    QMap<TQZButtonType, QMap<TQZButtonStyleType, QString> *>* buttonStyleConfig();


private:
    QMap<TQZButtonType, QMap<TQZButtonStyleType, QString> *>* m_buttonStyleConfig;

    TQZButtonType m_buttonType;


signals:

};

#endif // TQZBUTTON_H
