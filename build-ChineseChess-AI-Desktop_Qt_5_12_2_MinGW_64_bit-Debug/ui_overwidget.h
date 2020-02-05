/********************************************************************************
** Form generated from reading UI file 'overwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OVERWIDGET_H
#define UI_OVERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OverWidget
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *again;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *exit;
    QSpacerItem *horizontalSpacer_3;
    QLabel *Picture;
    QLabel *title;

    void setupUi(QWidget *OverWidget)
    {
        if (OverWidget->objectName().isEmpty())
            OverWidget->setObjectName(QString::fromUtf8("OverWidget"));
        OverWidget->resize(640, 470);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/B_BISHOP1.png"), QSize(), QIcon::Normal, QIcon::Off);
        OverWidget->setWindowIcon(icon);
        widget = new QWidget(OverWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 380, 640, 50));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        again = new QPushButton(widget);
        again->setObjectName(QString::fromUtf8("again"));

        horizontalLayout->addWidget(again);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        exit = new QPushButton(widget);
        exit->setObjectName(QString::fromUtf8("exit"));

        horizontalLayout->addWidget(exit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        Picture = new QLabel(OverWidget);
        Picture->setObjectName(QString::fromUtf8("Picture"));
        Picture->setGeometry(QRect(190, 120, 260, 200));
        title = new QLabel(OverWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(200, 40, 240, 60));

        retranslateUi(OverWidget);

        QMetaObject::connectSlotsByName(OverWidget);
    } // setupUi

    void retranslateUi(QWidget *OverWidget)
    {
        OverWidget->setWindowTitle(QApplication::translate("OverWidget", "\344\270\255\345\233\275\350\261\241\346\243\213", nullptr));
        again->setText(QApplication::translate("OverWidget", "\345\206\215\346\235\245\344\270\200\345\261\200", nullptr));
        exit->setText(QApplication::translate("OverWidget", "\351\200\200\345\207\272", nullptr));
        Picture->setText(QApplication::translate("OverWidget", "TextLabel", nullptr));
        title->setText(QApplication::translate("OverWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OverWidget: public Ui_OverWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OVERWIDGET_H
