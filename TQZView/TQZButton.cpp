#include "TQZButton.h"

#include <QFont>
#include <QMouseEvent>

#include <QDebug>


TQZButton::TQZButton(const QString &text, TQZButtonType buttonType, QWidget *parent):
    QPushButton(parent),
    m_buttonStyleConfig(nullptr),
    m_buttonType(buttonType)
{
    this->UpdateSelf(text);
}


void TQZButton::UpdateSelf(const QString &text) {
    this->setText(text);

    this->setStyleSheet(this->buttonStyleConfig()->find(m_buttonType).value()->find(DEFAULT).value());
}


void TQZButton::enterEvent(QEvent* event) {
    this->setStyleSheet(this->buttonStyleConfig()->find(m_buttonType).value()->find(MOVEIN).value());

    QPushButton::enterEvent(event);
}

void TQZButton::leaveEvent(QEvent* event) {
    this->setStyleSheet(this->buttonStyleConfig()->find(m_buttonType).value()->find(DEFAULT).value());

    QPushButton::enterEvent(event);
}


QMap<TQZButtonType, QMap<TQZButton::TQZButtonStyleType, QString>*>* TQZButton::buttonStyleConfig() {
    if (this->m_buttonStyleConfig == nullptr) {
        this->m_buttonStyleConfig = new QMap<TQZButtonType, QMap<TQZButtonStyleType, QString>*>;

        QMap<TQZButtonStyleType, QString> *commonButtonConfig = new QMap<TQZButtonStyleType, QString>;
        commonButtonConfig->insert(DEFAULT, "TQZButton { border: none; color: white; }");
        commonButtonConfig->insert(MOVEIN, "TQZButton { border-radius: 6px; border: none; background-color: rgb(63, 60, 60); color: white; }");

        QMap<TQZButtonStyleType, QString> *closeButtonConfig = new QMap<TQZButtonStyleType, QString>;
        closeButtonConfig->insert(DEFAULT, "TQZButton { border: none; color: white; }");
        closeButtonConfig->insert(MOVEIN, "TQZButton { border-radius: 6px; border: none; background-color: rgb(228, 64, 50); color: white; }");

        QMap<TQZButtonStyleType, QString> *lockButtonConfig = new QMap<TQZButtonStyleType, QString>;
        lockButtonConfig->insert(DEFAULT, "TQZButton { border-radius: 6px; border: none; background-color: rgba(228, 64, 50, 150); color: white; }");
        lockButtonConfig->insert(MOVEIN, "TQZButton { border-radius: 6px; border: none; background-color: rgba(228, 64, 50, 110); color: white; }");

        QMap<TQZButtonStyleType, QString> *messageButtonConfig = new QMap<TQZButtonStyleType, QString>;
        messageButtonConfig->insert(DEFAULT, "TQZButton { border-radius: 6px; border: none; background-color: rgba(250, 250, 250, 130); color: white; }");
        messageButtonConfig->insert(MOVEIN, "TQZButton { border-radius: 6px; border: none; background-color: rgba(245, 245, 245, 110); color: white; }");

        QMap<TQZButtonStyleType, QString> *cancelButtonConfig = new QMap<TQZButtonStyleType, QString>;
        cancelButtonConfig->insert(DEFAULT, "TQZButton { border-radius: 6px; border: none; background-color: rgba(252, 195, 30, 150); color: white; }");
        cancelButtonConfig->insert(MOVEIN, "TQZButton { border-radius: 6px; border: none; background-color: rgba(252, 195, 30, 110); color: white; }");


        this->m_buttonStyleConfig->insert(COMMON, commonButtonConfig);
        this->m_buttonStyleConfig->insert(CLOSE, closeButtonConfig);
        this->m_buttonStyleConfig->insert(LOCK, lockButtonConfig);
        this->m_buttonStyleConfig->insert(MESSAGE, messageButtonConfig);
        this->m_buttonStyleConfig->insert(CANCEL, cancelButtonConfig);

    }

    return this->m_buttonStyleConfig;
}


TQZButton::~TQZButton() {
    if (this->m_buttonStyleConfig != nullptr) {
        foreach (const TQZButtonType &key, this->m_buttonStyleConfig->keys()) {
            delete this->m_buttonStyleConfig->value(key);
            this->m_buttonStyleConfig->insert(key, nullptr);
        }

        delete this->m_buttonStyleConfig;
        this->m_buttonStyleConfig = nullptr;
    }
}

