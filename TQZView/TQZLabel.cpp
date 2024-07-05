#include "TQZLabel.h"

TQZLabel::TQZLabel(const QString &text, QWidget *parent) : QLabel(text, parent)
{
//    this->setStyleSheet("background-color: blue; color: white; font-size: 18px;");
    this->setStyleSheet("color: white; font-size: 18px;");

    QFont font("宋体", 15, QFont::Medium);
    this->setFont(font);
}
