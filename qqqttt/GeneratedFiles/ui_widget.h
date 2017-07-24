/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *connect;
    QPushButton *stop;
    QLineEdit *lineEdit;
    QLabel *statuslabel;
    QLineEdit *port;
    QLabel *Image;
    QPushButton *record;
    QPushButton *stoprecord;
    QPushButton *pushButton;
    QPushButton *run;
    QPushButton *left;
    QPushButton *back;
    QPushButton *right;
    QPushButton *stop_car;
    QPushButton *help;
    QPushButton *buzzer;
    QSlider *speed;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QRadioButton *mode;
    QPushButton *objectMode;
    QLabel *speeLabel;
    QLabel *frameRate;
    QPushButton *grayMode;
    QLabel *label_2;
    QPushButton *faceMode;
    QPushButton *srcMode;
    QLabel *videoName;
    QLabel *vedioText;
    QLabel *detectFaceLabel;
    QPushButton *loadFaceImgBtn;
    QLabel *faceDetectResault;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->setEnabled(true);
        Widget->resize(1123, 545);
        connect = new QPushButton(Widget);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(240, 9, 75, 23));
        stop = new QPushButton(Widget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(320, 9, 75, 23));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(400, 10, 113, 20));
        statuslabel = new QLabel(Widget);
        statuslabel->setObjectName(QStringLiteral("statuslabel"));
        statuslabel->setGeometry(QRect(240, 450, 320, 20));
        statuslabel->setFrameShape(QFrame::StyledPanel);
        port = new QLineEdit(Widget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(520, 10, 41, 20));
        Image = new QLabel(Widget);
        Image->setObjectName(QStringLiteral("Image"));
        Image->setGeometry(QRect(240, 40, 531, 371));
        record = new QPushButton(Widget);
        record->setObjectName(QStringLiteral("record"));
        record->setGeometry(QRect(790, 410, 75, 23));
        stoprecord = new QPushButton(Widget);
        stoprecord->setObjectName(QStringLiteral("stoprecord"));
        stoprecord->setGeometry(QRect(790, 440, 75, 23));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(790, 470, 75, 23));
        run = new QPushButton(Widget);
        run->setObjectName(QStringLiteral("run"));
        run->setGeometry(QRect(95, 55, 50, 50));
        left = new QPushButton(Widget);
        left->setObjectName(QStringLiteral("left"));
        left->setGeometry(QRect(20, 130, 50, 50));
        back = new QPushButton(Widget);
        back->setObjectName(QStringLiteral("back"));
        back->setGeometry(QRect(95, 205, 50, 50));
        right = new QPushButton(Widget);
        right->setObjectName(QStringLiteral("right"));
        right->setGeometry(QRect(170, 130, 50, 50));
        stop_car = new QPushButton(Widget);
        stop_car->setObjectName(QStringLiteral("stop_car"));
        stop_car->setGeometry(QRect(95, 130, 50, 50));
        help = new QPushButton(Widget);
        help->setObjectName(QStringLiteral("help"));
        help->setGeometry(QRect(890, 500, 75, 23));
        buzzer = new QPushButton(Widget);
        buzzer->setObjectName(QStringLiteral("buzzer"));
        buzzer->setGeometry(QRect(790, 500, 75, 23));
        speed = new QSlider(Widget);
        speed->setObjectName(QStringLiteral("speed"));
        speed->setGeometry(QRect(790, 80, 185, 31));
        speed->setMaximumSize(QSize(185, 16777215));
        speed->setMaximum(255);
        speed->setValue(200);
        speed->setOrientation(Qt::Horizontal);
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(880, 20, 64, 23));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(955, 20, 30, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(12);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        mode = new QRadioButton(Widget);
        mode->setObjectName(QStringLiteral("mode"));
        mode->setGeometry(QRect(20, 13, 45, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        mode->setFont(font1);
        objectMode = new QPushButton(Widget);
        objectMode->setObjectName(QStringLiteral("objectMode"));
        objectMode->setGeometry(QRect(20, 330, 75, 23));
        speeLabel = new QLabel(Widget);
        speeLabel->setObjectName(QStringLiteral("speeLabel"));
        speeLabel->setGeometry(QRect(1010, 80, 61, 20));
        speeLabel->setFrameShape(QFrame::StyledPanel);
        frameRate = new QLabel(Widget);
        frameRate->setObjectName(QStringLiteral("frameRate"));
        frameRate->setGeometry(QRect(610, 450, 71, 20));
        frameRate->setFrameShape(QFrame::StyledPanel);
        grayMode = new QPushButton(Widget);
        grayMode->setObjectName(QStringLiteral("grayMode"));
        grayMode->setGeometry(QRect(20, 370, 75, 23));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(790, 50, 61, 21));
        faceMode = new QPushButton(Widget);
        faceMode->setObjectName(QStringLiteral("faceMode"));
        faceMode->setGeometry(QRect(20, 410, 75, 23));
        srcMode = new QPushButton(Widget);
        srcMode->setObjectName(QStringLiteral("srcMode"));
        srcMode->setGeometry(QRect(20, 290, 75, 23));
        videoName = new QLabel(Widget);
        videoName->setObjectName(QStringLiteral("videoName"));
        videoName->setGeometry(QRect(30, 450, 91, 31));
        vedioText = new QLabel(Widget);
        vedioText->setObjectName(QStringLiteral("vedioText"));
        vedioText->setGeometry(QRect(130, 450, 71, 31));
        detectFaceLabel = new QLabel(Widget);
        detectFaceLabel->setObjectName(QStringLiteral("detectFaceLabel"));
        detectFaceLabel->setGeometry(QRect(850, 170, 160, 180));
        loadFaceImgBtn = new QPushButton(Widget);
        loadFaceImgBtn->setObjectName(QStringLiteral("loadFaceImgBtn"));
        loadFaceImgBtn->setGeometry(QRect(920, 440, 131, 23));
        faceDetectResault = new QLabel(Widget);
        faceDetectResault->setObjectName(QStringLiteral("faceDetectResault"));
        faceDetectResault->setGeometry(QRect(930, 405, 111, 21));

        retranslateUi(Widget);
        QObject::connect(pushButton, SIGNAL(clicked()), Widget, SLOT(close()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "WiFi Video Capture", 0));
        connect->setText(QApplication::translate("Widget", "\350\277\236\346\216\245", 0));
        stop->setText(QApplication::translate("Widget", "\346\226\255\345\274\200", 0));
        lineEdit->setText(QApplication::translate("Widget", "192.168.8.1", 0));
        statuslabel->setText(QString());
        port->setText(QApplication::translate("Widget", "8083", 0));
        Image->setText(QString());
        record->setText(QApplication::translate("Widget", "\350\247\206\351\242\221\345\275\225\345\210\266", 0));
        stoprecord->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\345\275\225\345\210\266", 0));
        pushButton->setText(QApplication::translate("Widget", "\345\205\263\351\227\255", 0));
        run->setText(QApplication::translate("Widget", "\345\211\215", 0));
        left->setText(QApplication::translate("Widget", "\345\267\246", 0));
        back->setText(QApplication::translate("Widget", "\345\220\216", 0));
        right->setText(QApplication::translate("Widget", "\345\217\263", 0));
        stop_car->setText(QApplication::translate("Widget", "\345\201\234", 0));
        help->setText(QApplication::translate("Widget", "\345\270\256\345\212\251", 0));
        buzzer->setText(QApplication::translate("Widget", "Buzzer", 0));
        label->setText(QApplication::translate("Widget", "\342\204\203", 0));
        mode->setText(QApplication::translate("Widget", "\346\250\241\345\274\217", 0));
        objectMode->setText(QApplication::translate("Widget", "\347\211\251\344\275\223\350\257\206\345\210\253", 0));
        speeLabel->setText(QString());
        frameRate->setText(QString());
        grayMode->setText(QApplication::translate("Widget", "\347\201\260\345\272\246\346\250\241\345\274\217", 0));
        label_2->setText(QApplication::translate("Widget", "\347\201\260\345\272\246\350\260\203\350\212\202", 0));
        faceMode->setText(QApplication::translate("Widget", "\344\272\272\350\204\270\350\257\206\345\210\253", 0));
        srcMode->setText(QApplication::translate("Widget", "\345\216\237\345\247\213\345\233\276\345\203\217", 0));
        videoName->setText(QApplication::translate("Widget", "\345\275\223\345\211\215\350\247\206\351\242\221\346\250\241\345\274\217\357\274\232", 0));
        vedioText->setText(QApplication::translate("Widget", "src mode", 0));
        detectFaceLabel->setText(QString());
        loadFaceImgBtn->setText(QApplication::translate("Widget", "\350\275\275\345\205\245\344\272\272\350\204\270\345\233\276\345\203\217", 0));
        faceDetectResault->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
