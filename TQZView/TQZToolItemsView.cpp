#include "TQZToolItemsView.h"

//#include "TQZButton.h"

TQZToolItemsView::TQZToolItemsView(double height, int itemCount, QWidget *parent):
    QGraphicsView(parent),
    m_itemCount(itemCount),
    m_height(height),
    m_minButton(nullptr),
    m_normalMaxButton(nullptr),
    m_closeButton(nullptr)
{
    this->setFixedSize(m_height * itemCount, m_height);
    this->setStyleSheet("background: transparent");
}


TQZButton *TQZToolItemsView::minButton() {
    if (this->m_minButton == nullptr) {
        this->m_minButton = new TQZButton("—", TQZButtonType::COMMON, this);
        this->m_minButton->setFixedSize(m_height, m_height);
    }

    return this->m_minButton;
}

TQZButton *TQZToolItemsView::normalMaxButton() {
    if (this->m_normalMaxButton == nullptr) {
        this->m_normalMaxButton = new TQZButton("囗", TQZButtonType::COMMON, this);
        this->m_normalMaxButton->move(this->minButton()->width(), 0);
        this->m_normalMaxButton->setFixedSize(m_height, m_height);
    }

    return this->m_normalMaxButton;
}

TQZButton *TQZToolItemsView::closeButton() {
    if (this->m_closeButton == nullptr) {
        this->m_closeButton = new TQZButton("X", TQZButtonType::CLOSE, this);
        this->m_closeButton->move(this->minButton()->width() + this->normalMaxButton()->width(), 0);
        this->m_closeButton->setFixedSize(m_height, m_height);
    }

    return this->m_closeButton;
}
