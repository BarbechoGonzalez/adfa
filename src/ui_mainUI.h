/********************************************************************************
** Form generated from reading UI file 'mainUI.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINUI_H
#define UI_MAINUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiDlg
{
public:
    QPushButton *Start;
    QPushButton *Stop;
    QTextEdit *InfoTag;
    QGraphicsView *Grafico;
    QLCDNumber *LCDhor;
    QLCDNumber *LCDmin;
    QLCDNumber *LCDseg;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *InfoText;
    QSlider *cotavision;
    QSlider *vellmax;
    QSlider *velgmax;
    QSlider *distanciadeseguridad;
    QSlider *distanciadegiro;
    QLabel *Lcota;
    QLabel *Lvell;
    QLabel *Lvelg;
    QLabel *LdisS;
    QLabel *LdisG;
    QPushButton *Reset;

    void setupUi(QWidget *guiDlg)
    {
        if (guiDlg->objectName().isEmpty())
            guiDlg->setObjectName(QString::fromUtf8("guiDlg"));
        guiDlg->resize(838, 559);
        Start = new QPushButton(guiDlg);
        Start->setObjectName(QString::fromUtf8("Start"));
        Start->setGeometry(QRect(20, 500, 81, 51));
        Stop = new QPushButton(guiDlg);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setGeometry(QRect(110, 500, 81, 51));
        InfoTag = new QTextEdit(guiDlg);
        InfoTag->setObjectName(QString::fromUtf8("InfoTag"));
        InfoTag->setGeometry(QRect(10, 80, 271, 81));
        Grafico = new QGraphicsView(guiDlg);
        Grafico->setObjectName(QString::fromUtf8("Grafico"));
        Grafico->setGeometry(QRect(290, 10, 541, 541));
        LCDhor = new QLCDNumber(guiDlg);
        LCDhor->setObjectName(QString::fromUtf8("LCDhor"));
        LCDhor->setEnabled(true);
        LCDhor->setGeometry(QRect(20, 20, 61, 51));
#ifndef QT_NO_ACCESSIBILITY
        LCDhor->setAccessibleName(QString::fromUtf8(""));
#endif // QT_NO_ACCESSIBILITY
        LCDhor->setDigitCount(2);
        LCDmin = new QLCDNumber(guiDlg);
        LCDmin->setObjectName(QString::fromUtf8("LCDmin"));
        LCDmin->setGeometry(QRect(100, 20, 61, 51));
        LCDmin->setDigitCount(2);
        LCDseg = new QLCDNumber(guiDlg);
        LCDseg->setObjectName(QString::fromUtf8("LCDseg"));
        LCDseg->setGeometry(QRect(180, 30, 51, 41));
        LCDseg->setDigitCount(2);
        label = new QLabel(guiDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 0, 66, 17));
        label_2 = new QLabel(guiDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 0, 66, 17));
        label_3 = new QLabel(guiDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 0, 81, 17));
        InfoText = new QTextEdit(guiDlg);
        InfoText->setObjectName(QString::fromUtf8("InfoText"));
        InfoText->setGeometry(QRect(10, 170, 271, 121));
        cotavision = new QSlider(guiDlg);
        cotavision->setObjectName(QString::fromUtf8("cotavision"));
        cotavision->setGeometry(QRect(30, 300, 29, 160));
        cotavision->setMaximum(48);
        cotavision->setSingleStep(0);
        cotavision->setValue(16);
        cotavision->setOrientation(Qt::Vertical);
        vellmax = new QSlider(guiDlg);
        vellmax->setObjectName(QString::fromUtf8("vellmax"));
        vellmax->setGeometry(QRect(80, 300, 29, 160));
        vellmax->setMaximum(600);
        vellmax->setSingleStep(5);
        vellmax->setValue(350);
        vellmax->setOrientation(Qt::Vertical);
        velgmax = new QSlider(guiDlg);
        velgmax->setObjectName(QString::fromUtf8("velgmax"));
        velgmax->setGeometry(QRect(130, 300, 29, 160));
        velgmax->setMaximum(30);
        velgmax->setValue(22);
        velgmax->setOrientation(Qt::Vertical);
        distanciadeseguridad = new QSlider(guiDlg);
        distanciadeseguridad->setObjectName(QString::fromUtf8("distanciadeseguridad"));
        distanciadeseguridad->setGeometry(QRect(180, 300, 29, 160));
        distanciadeseguridad->setMaximum(500);
        distanciadeseguridad->setSingleStep(200);
        distanciadeseguridad->setValue(440);
        distanciadeseguridad->setOrientation(Qt::Vertical);
        distanciadegiro = new QSlider(guiDlg);
        distanciadegiro->setObjectName(QString::fromUtf8("distanciadegiro"));
        distanciadegiro->setGeometry(QRect(230, 300, 29, 160));
        distanciadegiro->setMaximum(500);
        distanciadegiro->setSingleStep(200);
        distanciadegiro->setValue(400);
        distanciadegiro->setOrientation(Qt::Vertical);
        Lcota = new QLabel(guiDlg);
        Lcota->setObjectName(QString::fromUtf8("Lcota"));
        Lcota->setGeometry(QRect(10, 470, 66, 17));
        Lcota->setAlignment(Qt::AlignCenter);
        Lvell = new QLabel(guiDlg);
        Lvell->setObjectName(QString::fromUtf8("Lvell"));
        Lvell->setGeometry(QRect(60, 470, 66, 17));
        Lvell->setAlignment(Qt::AlignCenter);
        Lvelg = new QLabel(guiDlg);
        Lvelg->setObjectName(QString::fromUtf8("Lvelg"));
        Lvelg->setGeometry(QRect(110, 470, 66, 17));
        Lvelg->setAlignment(Qt::AlignCenter);
        LdisS = new QLabel(guiDlg);
        LdisS->setObjectName(QString::fromUtf8("LdisS"));
        LdisS->setGeometry(QRect(160, 470, 66, 17));
        LdisS->setAlignment(Qt::AlignCenter);
        LdisG = new QLabel(guiDlg);
        LdisG->setObjectName(QString::fromUtf8("LdisG"));
        LdisG->setGeometry(QRect(210, 470, 66, 17));
        LdisG->setAlignment(Qt::AlignCenter);
        Reset = new QPushButton(guiDlg);
        Reset->setObjectName(QString::fromUtf8("Reset"));
        Reset->setGeometry(QRect(200, 500, 81, 51));

        retranslateUi(guiDlg);

        QMetaObject::connectSlotsByName(guiDlg);
    } // setupUi

    void retranslateUi(QWidget *guiDlg)
    {
        guiDlg->setWindowTitle(QApplication::translate("guiDlg", "controller", 0, QApplication::UnicodeUTF8));
        Start->setText(QApplication::translate("guiDlg", "Start", 0, QApplication::UnicodeUTF8));
        Stop->setText(QApplication::translate("guiDlg", "Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        LCDmin->setWhatsThis(QApplication::translate("guiDlg", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        label->setText(QApplication::translate("guiDlg", "  HORAS", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("guiDlg", "MINUTOS", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("guiDlg", "SEGUNDOS", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cotavision->setToolTip(QApplication::translate("guiDlg", "Cota de vision lateral", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        cotavision->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        vellmax->setToolTip(QApplication::translate("guiDlg", "Velocidad lineal maxima ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        vellmax->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        vellmax->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        vellmax->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_TOOLTIP
        velgmax->setToolTip(QApplication::translate("guiDlg", "Velocidad maxima de giro", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        velgmax->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        distanciadeseguridad->setToolTip(QApplication::translate("guiDlg", "Distancia para detectar esquinas", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        distanciadegiro->setToolTip(QApplication::translate("guiDlg", "Distancia a la que se girara", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Lcota->setText(QApplication::translate("guiDlg", "0", 0, QApplication::UnicodeUTF8));
        Lvell->setText(QApplication::translate("guiDlg", "0", 0, QApplication::UnicodeUTF8));
        Lvelg->setText(QApplication::translate("guiDlg", "0", 0, QApplication::UnicodeUTF8));
        LdisS->setText(QApplication::translate("guiDlg", "0", 0, QApplication::UnicodeUTF8));
        LdisG->setText(QApplication::translate("guiDlg", "0", 0, QApplication::UnicodeUTF8));
        Reset->setText(QApplication::translate("guiDlg", "Reset", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class guiDlg: public Ui_guiDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINUI_H
