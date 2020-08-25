/********************************************************************************
** Form generated from reading UI file 'OctreeOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCTREEOPTIONS_H
#define UI_OCTREEOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OctreeOptions
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *Cancel;
    QPushButton *Ok;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *variation;

    void setupUi(QDialog *OctreeOptions)
    {
        if (OctreeOptions->objectName().isEmpty())
            OctreeOptions->setObjectName(QString::fromUtf8("OctreeOptions"));
        OctreeOptions->resize(433, 336);
        horizontalLayoutWidget = new QWidget(OctreeOptions);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 270, 401, 51));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Cancel = new QPushButton(horizontalLayoutWidget);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));

        horizontalLayout->addWidget(Cancel);

        Ok = new QPushButton(horizontalLayoutWidget);
        Ok->setObjectName(QString::fromUtf8("Ok"));

        horizontalLayout->addWidget(Ok);

        formLayoutWidget = new QWidget(OctreeOptions);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(50, 60, 331, 123));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        variation = new QDoubleSpinBox(formLayoutWidget);
        variation->setObjectName(QString::fromUtf8("variation"));
        variation->setDecimals(9);
        variation->setMaximum(0.400000000000000);
        variation->setSingleStep(0.000001000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, variation);


        retranslateUi(OctreeOptions);

        Ok->setDefault(true);


        QMetaObject::connectSlotsByName(OctreeOptions);
    } // setupUi

    void retranslateUi(QDialog *OctreeOptions)
    {
        OctreeOptions->setWindowTitle(QCoreApplication::translate("OctreeOptions", "OctreeOptions", nullptr));
        Cancel->setText(QCoreApplication::translate("OctreeOptions", "Cancel", nullptr));
        Ok->setText(QCoreApplication::translate("OctreeOptions", "Ok", nullptr));
        label->setText(QCoreApplication::translate("OctreeOptions", "Surface Variation Threshold", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OctreeOptions: public Ui_OctreeOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCTREEOPTIONS_H
