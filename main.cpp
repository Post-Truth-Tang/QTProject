#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "TQZController/TQZMainController.h"
#include "TQZController/TestController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "QtProject_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

//    TestController testController;
//    testController.show();

    TQZMainController mainController;
    mainController.show();

    return a.exec();
}
