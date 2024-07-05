#include "TQZMessageController.h"

#include <QDebug>


TQZMessageController::TQZMessageController(QWidget *parent):
    IController(parent),
    m_tableWidget(nullptr),
    m_closeButton(nullptr)
{
    ResetWindow(0.6, 0.84);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

void TQZMessageController::insertMessage(QString timeText, QString messageText, QString interfaceText) {
    int row = 0; // tableWidget->rowCount()
    this->m_tableWidget->insertRow(row);

    this->m_tableWidget->setItem(row, 0, new QTableWidgetItem(timeText));
    this->m_tableWidget->setItem(row, 1, new QTableWidgetItem(messageText));
    this->m_tableWidget->setItem(row, 2, new QTableWidgetItem(interfaceText));
}

void TQZMessageController::clear() {
    this->tableWidget()->clearContents();
    this->tableWidget()->setRowCount(0);
}


QTableWidget *TQZMessageController::tableWidget() {
    if (this->m_tableWidget == nullptr) {
        this->m_tableWidget = new QTableWidget(this);
        this->m_tableWidget->move(this->closeButton()->height() * 2, this->closeButton()->height() * 2);
        this->m_tableWidget->setFixedSize(this->width() - this->m_tableWidget->x() * 2, this->height() - this->m_tableWidget->y() * 2);
        this->m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        this->m_tableWidget->setColumnCount(3); // set feature count.

        // # set one column width. (make 0|1|2 to enum type.)
        this->m_tableWidget->setColumnWidth(0, this->m_tableWidget->width() * 0.15);
        this->m_tableWidget->setColumnWidth(1, this->m_tableWidget->width() * 0.70);
        this->m_tableWidget->setColumnWidth(2, this->m_tableWidget->width() * 0.15);

        this->m_tableWidget->setHorizontalHeaderLabels(QStringList() << "time" << "message" << "interface");
        this->m_tableWidget->setStyleSheet("QTableWidget {border-radius: 6px; border: none; background-color: rgba(250, 250, 250, 180); selection-background-color: darkgray; }");
        this->m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // can not editable.
        this->m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // only can select one row.
    }

    return this->m_tableWidget;
}


TQZButton *TQZMessageController::closeButton() {
    if (this->m_closeButton == nullptr) {
        this->m_closeButton = new TQZButton("X", TQZButtonType::CLOSE, this);
        this->m_closeButton->move(this->width() - 30, 0);
        this->m_closeButton->setFixedSize(30, 30);
        this->m_closeButton->connect(this->m_closeButton, &TQZButton::clicked, this, &TQZMessageController::close);
    }

    return this->m_closeButton;
}


void TQZMessageController::resizeEvent(QResizeEvent* event)
{

    QMainWindow::resizeEvent(event);
}
