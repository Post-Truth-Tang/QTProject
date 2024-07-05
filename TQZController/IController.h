#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QMainWindow>
#include <QSettings>
#include "ui_mainwindow.h"

#include <QScreen>

#include "TQZModel/TQZAccountModel.h"

class IController : public QMainWindow
{
    Q_OBJECT
public:
    explicit IController(QWidget *parent = nullptr);
    virtual ~IController();

protected:
    virtual void ResetWindow(double widthScale, double heightScale);

private:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    virtual void paintEvent(QPaintEvent *event);


protected:
    QMap<QString, TQZAccountModel>* accountModels(QString settingPath="./config/iniTest.ini");


private:
    bool m_moveable;
    QPoint z;

    QMap<QString, TQZAccountModel>* m_accountModels;

signals:

};

#endif // ICONTROLLER_H
