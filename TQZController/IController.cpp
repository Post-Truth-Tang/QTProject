#include "IController.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPainter>

#include <QWidget>
#include "IController.h"

#include <QMap>


IController::IController(QWidget *parent) :
    QMainWindow(parent),
    m_moveable(false),
    m_accountModels(nullptr)
{

}


QMap<QString, TQZAccountModel>* IController::accountModels(QString settingPath) {
    if (this->m_accountModels == nullptr) {
        this->m_accountModels = new QMap<QString, TQZAccountModel>();

        QSettings setting(settingPath, QSettings::IniFormat);

        QStringList groupList = setting.childGroups();
        foreach (const QString &group, groupList) {
            QMap<QString, QString> accountMap;

            setting.beginGroup(group);
            foreach (const QString &key, setting.allKeys()) {
                accountMap.insert(key, setting.value(key).toString());
            }
            setting.endGroup();

            this->m_accountModels->insert(group, TQZAccountModel(accountMap));
        }
    }

    return this->m_accountModels;
}


void IController::ResetWindow(double widthScale, double heightScale) {
    widthScale = (widthScale > 1) ? 1 : widthScale;
    heightScale = (heightScale > 1) ? 1 : heightScale;

    QScreen *screen = qApp->primaryScreen();

    int screenWidth = screen->size().width();
    int screenHeight = screen->size().height();
    this->resize(screenWidth * widthScale, screenHeight * heightScale);
    this->move(screenWidth * (1 - widthScale) * 0.5, screenHeight * (1 - heightScale) * 0.5);

    this->setAttribute(Qt::WA_TranslucentBackground);
}

void IController::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor(50, 50, 50, 248)));
    painter.setPen(Qt::transparent);

    QRect rect = this->rect();
    rect.setWidth(rect.width() - 1);
    rect.setHeight(rect.height() - 1);
    painter.drawRoundedRect(rect, 6, 6);

    QWidget::paintEvent(event);
}

void IController::mousePressEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    QWidget::mousePressEvent(event);

    QPoint y = event->globalPos();
    QPoint x = this->geometry().topLeft();
    this->z = y - x;

    this->m_moveable = true;
}

void IController::mouseMoveEvent(QMouseEvent *event) {
    if (!this->m_moveable)
        return;

    QWidget::mouseMoveEvent(event);

    QPoint y = event->globalPos();
    QPoint x = y - this->z;


    if (this->isMaximized())
        return;

    this->move(x);
}

void IController::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    QWidget::mouseReleaseEvent(event);

    this->m_moveable = false;
}

void IController::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() != Qt::RightButton)
        return;

    QWidget::mouseDoubleClickEvent(event);
}


IController::~IController() {
    if (this->m_accountModels != nullptr) {
        delete m_accountModels;
        this->m_accountModels = nullptr;
    }
}
