#include "TQZTradeButtonView.h"

TQZTradeButtonView::TQZTradeButtonView(double width, double buttonHeight, QWidget *parent):
    QGraphicsView(parent),
    m_tradeButton(nullptr),
    m_cancelAllButton(nullptr),
    m_width(width),
    m_buttonHeight(buttonHeight)
{
    this->setFixedSize(this->m_width, this->cancelAllButton()->y() + this->cancelAllButton()->height());
    this->setStyleSheet("background: transparent");
}


TQZButton *TQZTradeButtonView::tradeButton() {
    if (this->m_tradeButton == nullptr) {
        this->m_tradeButton = new TQZButton("One Piece trade", TQZButtonType::LOCK, this);
        this->m_tradeButton->setFixedSize(m_width, m_buttonHeight);
    }

    return this->m_tradeButton;
}
TQZButton *TQZTradeButtonView::cancelAllButton() {
    if (this->m_cancelAllButton == nullptr) {
        this->m_cancelAllButton = new TQZButton("cancel all", TQZButtonType::CANCEL, this);
        this->m_cancelAllButton->move(this->tradeButton()->x(), this->tradeButton()->y() + this->tradeButton()->height() + 20); // 20 is edge.
        this->m_cancelAllButton->setFixedSize(this->tradeButton()->width(), this->tradeButton()->height() * 0.5);
    }

    return this->m_cancelAllButton;
}
