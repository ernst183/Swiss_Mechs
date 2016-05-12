/********************************************************************************
** Form generated from reading UI file 'littlegui.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LITTLEGUI_H
#define UI_LITTLEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LittleGui
{
public:
    QLabel *label;
    QPushButton *liveImage;

    void setupUi(QDialog *LittleGui)
    {
        if (LittleGui->objectName().isEmpty())
            LittleGui->setObjectName(QStringLiteral("LittleGui"));
        LittleGui->resize(711, 416);
        label = new QLabel(LittleGui);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 180, 141, 17));
        liveImage = new QPushButton(LittleGui);
        liveImage->setObjectName(QStringLiteral("liveImage"));
        liveImage->setGeometry(QRect(10, 380, 97, 27));

        retranslateUi(LittleGui);

        QMetaObject::connectSlotsByName(LittleGui);
    } // setupUi

    void retranslateUi(QDialog *LittleGui)
    {
        LittleGui->setWindowTitle(QApplication::translate("LittleGui", "LittleGui", 0));
        label->setText(QApplication::translate("LittleGui", "This will be an image", 0));
        liveImage->setText(QApplication::translate("LittleGui", "Live", 0));
    } // retranslateUi

};

namespace Ui {
    class LittleGui: public Ui_LittleGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LITTLEGUI_H
