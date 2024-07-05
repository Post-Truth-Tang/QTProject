#include "TQZBanView.h"


TQZBanView::TQZBanView(double width, QWidget *parent):
    QGraphicsView(parent),
    m_banButton(nullptr),
    m_accountsComboBox(nullptr),
    m_messageButton(nullptr),
    m_inner_widget_height(35),
    m_width(width),
    m_height(m_inner_widget_height * 2 + 10) // 10 is edge.
{
    this->setFixedSize(this->m_width, this->m_height);
    this->setStyleSheet("background: transparent");
}


TQZButton *TQZBanView::banButton() {
    if (this->m_banButton == nullptr) {
        this->m_banButton = new TQZButton("lock", TQZButtonType::LOCK, this);
        m_banButton->setFixedSize((this->width() - 10) * 2 / 7, this->m_inner_widget_height);
    }

    return this->m_banButton;
}


QComboBox *TQZBanView::accountsComboBox() {
    if (this->m_accountsComboBox == nullptr) {
        this->m_accountsComboBox = new QComboBox(this);
        this->m_accountsComboBox->setFixedSize((this->width() - 10) * 5 / 7, this->m_inner_widget_height);
        this->m_accountsComboBox->move(this->width() - this->m_accountsComboBox->width(), 0);
        this->m_accountsComboBox->setStyleSheet("background-color: white; selection-background-color: red;");
    }

    return this->m_accountsComboBox;
}

TQZButton *TQZBanView::messageButton() {
    if (this->m_messageButton == nullptr) {
        this->m_messageButton = new TQZButton("message", TQZButtonType::MESSAGE, this);
        this->m_messageButton->setFixedSize(this->width(), this->m_inner_widget_height);
        this->m_messageButton->move(0, this->height() - this->m_messageButton->height());

        this->m_messageButton->connect(this->m_messageButton, &TQZButton::clicked, this, [=](){
            this->m_messageButton->setText("message");
        });
    }

    return this->m_messageButton;
}
