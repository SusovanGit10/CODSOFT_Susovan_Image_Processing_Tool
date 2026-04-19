/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <imageview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout;
    ImageView *imageView;
    QWidget *widgetBottom;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QPushButton *btnExit;
    QPushButton *btnReset;
    QSlider *sliderContrast;
    QPushButton *btnFlipV;
    QPushButton *btnRedo;
    QPushButton *btnGray;
    QPushButton *btnEdge;
    QPushButton *btnSharpen;
    QSlider *sliderR;
    QPushButton *btnRotate;
    QPushButton *btnBlur;
    QPushButton *btnSave;
    QPushButton *btnUndo;
    QPushButton *btnFlipH;
    QSlider *sliderG;
    QPushButton *btnOpen;
    QSlider *sliderBrightness;
    QPushButton *btnResize;
    QPushButton *btnCropManual;
    QSlider *sliderB;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 534);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        widgetTop = new QWidget(centralwidget);
        widgetTop->setObjectName("widgetTop");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widgetTop->sizePolicy().hasHeightForWidth());
        widgetTop->setSizePolicy(sizePolicy1);
        widgetTop->setMinimumSize(QSize(0, 400));
        horizontalLayout = new QHBoxLayout(widgetTop);
        horizontalLayout->setObjectName("horizontalLayout");
        imageView = new ImageView(widgetTop);
        imageView->setObjectName("imageView");
        sizePolicy1.setHeightForWidth(imageView->sizePolicy().hasHeightForWidth());
        imageView->setSizePolicy(sizePolicy1);
        imageView->setMinimumSize(QSize(400, 300));

        horizontalLayout->addWidget(imageView);


        verticalLayout->addWidget(widgetTop);

        widgetBottom = new QWidget(centralwidget);
        widgetBottom->setObjectName("widgetBottom");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetBottom->sizePolicy().hasHeightForWidth());
        widgetBottom->setSizePolicy(sizePolicy2);
        widgetBottom->setMinimumSize(QSize(0, 150));
        horizontalLayout_2 = new QHBoxLayout(widgetBottom);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        btnExit = new QPushButton(widgetBottom);
        btnExit->setObjectName("btnExit");

        gridLayout->addWidget(btnExit, 3, 4, 1, 1);

        btnReset = new QPushButton(widgetBottom);
        btnReset->setObjectName("btnReset");

        gridLayout->addWidget(btnReset, 3, 3, 1, 1);

        sliderContrast = new QSlider(widgetBottom);
        sliderContrast->setObjectName("sliderContrast");
        sliderContrast->setMaximum(100);
        sliderContrast->setSliderPosition(50);
        sliderContrast->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(sliderContrast, 0, 3, 1, 2);

        btnFlipV = new QPushButton(widgetBottom);
        btnFlipV->setObjectName("btnFlipV");

        gridLayout->addWidget(btnFlipV, 2, 3, 1, 1);

        btnRedo = new QPushButton(widgetBottom);
        btnRedo->setObjectName("btnRedo");

        gridLayout->addWidget(btnRedo, 3, 1, 1, 1);

        btnGray = new QPushButton(widgetBottom);
        btnGray->setObjectName("btnGray");

        gridLayout->addWidget(btnGray, 1, 1, 1, 1);

        btnEdge = new QPushButton(widgetBottom);
        btnEdge->setObjectName("btnEdge");

        gridLayout->addWidget(btnEdge, 2, 1, 1, 1);

        btnSharpen = new QPushButton(widgetBottom);
        btnSharpen->setObjectName("btnSharpen");

        gridLayout->addWidget(btnSharpen, 1, 3, 1, 1);

        sliderR = new QSlider(widgetBottom);
        sliderR->setObjectName("sliderR");
        sliderR->setMaximum(100);
        sliderR->setSliderPosition(50);
        sliderR->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(sliderR, 4, 0, 1, 2);

        btnRotate = new QPushButton(widgetBottom);
        btnRotate->setObjectName("btnRotate");

        gridLayout->addWidget(btnRotate, 2, 0, 1, 1);

        btnBlur = new QPushButton(widgetBottom);
        btnBlur->setObjectName("btnBlur");

        gridLayout->addWidget(btnBlur, 1, 2, 1, 1);

        btnSave = new QPushButton(widgetBottom);
        btnSave->setObjectName("btnSave");

        gridLayout->addWidget(btnSave, 3, 2, 1, 1);

        btnUndo = new QPushButton(widgetBottom);
        btnUndo->setObjectName("btnUndo");

        gridLayout->addWidget(btnUndo, 3, 0, 1, 1);

        btnFlipH = new QPushButton(widgetBottom);
        btnFlipH->setObjectName("btnFlipH");

        gridLayout->addWidget(btnFlipH, 2, 2, 1, 1);

        sliderG = new QSlider(widgetBottom);
        sliderG->setObjectName("sliderG");
        sliderG->setMaximum(100);
        sliderG->setSliderPosition(50);
        sliderG->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(sliderG, 4, 2, 1, 1);

        btnOpen = new QPushButton(widgetBottom);
        btnOpen->setObjectName("btnOpen");

        gridLayout->addWidget(btnOpen, 1, 0, 1, 1);

        sliderBrightness = new QSlider(widgetBottom);
        sliderBrightness->setObjectName("sliderBrightness");
        sliderBrightness->setMaximum(100);
        sliderBrightness->setSliderPosition(50);
        sliderBrightness->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(sliderBrightness, 0, 0, 1, 2);

        btnResize = new QPushButton(widgetBottom);
        btnResize->setObjectName("btnResize");

        gridLayout->addWidget(btnResize, 1, 4, 1, 1);

        btnCropManual = new QPushButton(widgetBottom);
        btnCropManual->setObjectName("btnCropManual");

        gridLayout->addWidget(btnCropManual, 2, 4, 1, 1);

        sliderB = new QSlider(widgetBottom);
        sliderB->setObjectName("sliderB");
        sliderB->setMaximum(100);
        sliderB->setSliderPosition(50);
        sliderB->setOrientation(Qt::Orientation::Horizontal);

        gridLayout->addWidget(sliderB, 4, 3, 1, 2);


        horizontalLayout_2->addLayout(gridLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widgetBottom);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        btnReset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        btnFlipV->setText(QCoreApplication::translate("MainWindow", "FlipV", nullptr));
        btnRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        btnGray->setText(QCoreApplication::translate("MainWindow", "Gray", nullptr));
        btnEdge->setText(QCoreApplication::translate("MainWindow", "Edge", nullptr));
        btnSharpen->setText(QCoreApplication::translate("MainWindow", "Sharpen", nullptr));
        btnRotate->setText(QCoreApplication::translate("MainWindow", "Rotate", nullptr));
        btnBlur->setText(QCoreApplication::translate("MainWindow", "Blur", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        btnUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        btnFlipH->setText(QCoreApplication::translate("MainWindow", "FlipH", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        btnResize->setText(QCoreApplication::translate("MainWindow", "Resize", nullptr));
        btnCropManual->setText(QCoreApplication::translate("MainWindow", "CropManual", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
