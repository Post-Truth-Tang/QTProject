#include "ITableWidget.h"

#include <QDebug>

ITableWidget::ITableWidget(QWidget *parent):
    QTableWidget(parent),
    m_headerList(nullptr)
{
    this->setSelectionMode(QAbstractItemView::SingleSelection); // only can select one row.
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // can not editable.
    this->setSelectionBehavior(QAbstractItemView::SelectRows); // select one row.
    this->setStyleSheet("QTableWidget {border: none; background-color: rgba(250, 250, 250, 118); selection-background-color: darkgray; }");
}


void ITableWidget::resizeEvent(QResizeEvent* event) {
    for (int i = 0; i < this->m_headerList->count(); i++) {
        this->setColumnWidth(i, this->width() * (1.0 / this->m_headerList->count()));
    }

    QWidget::resizeEvent(event);
}


ITableWidget::~ITableWidget() {

}
