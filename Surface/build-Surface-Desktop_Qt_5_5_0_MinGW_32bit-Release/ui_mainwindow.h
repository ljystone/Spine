/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditLPush;
    QLabel *label_5;
    QLabel *label_2;
    QLineEdit *lineEditrRPush;
    QLabel *label_6;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEditLMove;
    QLabel *label_7;
    QLabel *label_4;
    QLineEdit *lineEditRMove;
    QLabel *label_8;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonStart;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButtonStop;
    QSpacerItem *horizontalSpacer_7;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(383, 352);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget_3 = new QWidget(centralWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(widget_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(81, 18, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_9 = new QLabel(widget_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy1);
        label_9->setMinimumSize(QSize(60, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\350\241\214\346\245\267"));
        font.setPointSize(16);
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_9);

        horizontalSpacer_2 = new QSpacerItem(80, 18, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout->addWidget(widget_3, 0, 0, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditLPush = new QLineEdit(widget);
        lineEditLPush->setObjectName(QStringLiteral("lineEditLPush"));
        sizePolicy.setHeightForWidth(lineEditLPush->sizePolicy().hasHeightForWidth());
        lineEditLPush->setSizePolicy(sizePolicy);
        lineEditLPush->setMaximumSize(QSize(71, 16777215));
        lineEditLPush->setReadOnly(true);

        horizontalLayout->addWidget(lineEditLPush);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(9);
        label_5->setFont(font1);

        horizontalLayout->addWidget(label_5);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEditrRPush = new QLineEdit(widget);
        lineEditrRPush->setObjectName(QStringLiteral("lineEditrRPush"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEditrRPush->sizePolicy().hasHeightForWidth());
        lineEditrRPush->setSizePolicy(sizePolicy3);
        lineEditrRPush->setMaximumSize(QSize(70, 16777215));
        lineEditrRPush->setReadOnly(true);

        horizontalLayout->addWidget(lineEditrRPush);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(18, 38, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEditLMove = new QLineEdit(widget);
        lineEditLMove->setObjectName(QStringLiteral("lineEditLMove"));
        sizePolicy3.setHeightForWidth(lineEditLMove->sizePolicy().hasHeightForWidth());
        lineEditLMove->setSizePolicy(sizePolicy3);
        lineEditLMove->setMaximumSize(QSize(70, 16777215));
        lineEditLMove->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditLMove);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font2;
        font2.setFamily(QStringLiteral("Agency FB"));
        font2.setPointSize(12);
        label_7->setFont(font2);

        horizontalLayout_2->addWidget(label_7);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEditRMove = new QLineEdit(widget);
        lineEditRMove->setObjectName(QStringLiteral("lineEditRMove"));
        sizePolicy3.setHeightForWidth(lineEditRMove->sizePolicy().hasHeightForWidth());
        lineEditRMove->setSizePolicy(sizePolicy3);
        lineEditRMove->setMaximumSize(QSize(70, 16777215));
        lineEditRMove->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEditRMove);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font2);

        horizontalLayout_2->addWidget(label_8);


        verticalLayout->addLayout(horizontalLayout_2);

        lineEditLPush->raise();
        label->raise();
        label_2->raise();
        label_5->raise();
        lineEditrRPush->raise();
        label_6->raise();
        lineEditLPush->raise();
        label->raise();
        label_2->raise();
        lineEditrRPush->raise();
        label_5->raise();
        label_6->raise();
        label_8->raise();
        label_3->raise();
        label_7->raise();
        lineEditLMove->raise();
        lineEditRMove->raise();
        label_4->raise();

        gridLayout->addWidget(widget, 1, 0, 1, 1);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButtonStart = new QPushButton(widget_2);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));

        horizontalLayout_3->addWidget(pushButtonStart);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        pushButtonStop = new QPushButton(widget_2);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));

        horizontalLayout_3->addWidget(pushButtonStop);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        gridLayout->addWidget(widget_2, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 383, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "sur", 0));
        label_9->setText(QApplication::translate("MainWindow", "\345\216\213\345\212\233\344\275\215\347\247\273\346\265\213\351\207\217\347\263\273\347\273\237", 0));
        label->setText(QApplication::translate("MainWindow", "\345\267\246\344\276\247\345\216\213\345\212\233\345\200\274\357\274\232", 0));
        label_5->setText(QApplication::translate("MainWindow", "N", 0));
        label_2->setText(QApplication::translate("MainWindow", "\345\217\263\344\276\247\345\216\213\345\212\233\345\200\274\357\274\232", 0));
        label_6->setText(QApplication::translate("MainWindow", "N", 0));
        label_3->setText(QApplication::translate("MainWindow", "\345\267\246\344\276\247\344\275\215\347\247\273\351\207\217\357\274\232", 0));
        label_7->setText(QApplication::translate("MainWindow", "m", 0));
        label_4->setText(QApplication::translate("MainWindow", "\345\217\263\344\276\247\344\275\215\347\247\273\351\207\217\357\274\232", 0));
        label_8->setText(QApplication::translate("MainWindow", "m", 0));
        pushButtonStart->setText(QApplication::translate("MainWindow", "start", 0));
        pushButtonStop->setText(QApplication::translate("MainWindow", "stop", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
