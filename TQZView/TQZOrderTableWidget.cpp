#include "TQZOrderTableWidget.h"

TQZOrderTableWidget::TQZOrderTableWidget(QWidget *parent) : ITableWidget(parent)
{
    this->m_headerList = new QStringList({"feature1", "feature2", "feature3", "feature4", "feature5"});

    this->setColumnCount(this->m_headerList->count());
    this->setHorizontalHeaderLabels(*this->m_headerList);
}


TQZOrderTableWidget::~TQZOrderTableWidget() {
    if (this->m_headerList != nullptr) {
        delete this->m_headerList;
        this->m_headerList = nullptr;
    }
}
