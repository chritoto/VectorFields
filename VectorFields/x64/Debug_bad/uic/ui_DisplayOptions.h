/********************************************************************************
** Form generated from reading UI file 'DisplayOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYOPTIONS_H
#define UI_DISPLAYOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayOptions
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
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *width;
    QLabel *label_2;
    QSpinBox *height;
    QLabel *label_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *angle;
    QLabel *label_5;
    QLabel *label_6;
    QDoubleSpinBox *background;
    QGroupBox *groupBox;
    QLabel *label_7;
    QSpinBox *Levels;
    QGroupBox *groupBox_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QComboBox *comboBox_7;
    QComboBox *comboBox_1;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_16;
    QDoubleSpinBox *planthresh;
    QLabel *label_17;
    QLabel *label_18;
    QCheckBox *follow;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *ambient;
    QLabel *label_20;

    void setupUi(QWidget *DisplayOptions)
    {
        if (DisplayOptions->objectName().isEmpty())
            DisplayOptions->setObjectName(QString::fromUtf8("DisplayOptions"));
        DisplayOptions->resize(481, 555);
        horizontalLayoutWidget = new QWidget(DisplayOptions);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(50, 470, 401, 51));
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

        formLayoutWidget = new QWidget(DisplayOptions);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(70, 20, 331, 444));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        width = new QSpinBox(formLayoutWidget);
        width->setObjectName(QString::fromUtf8("width"));
        width->setMinimum(1);
        width->setMaximum(4000);
        width->setValue(500);

        horizontalLayout_2->addWidget(width);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        height = new QSpinBox(formLayoutWidget);
        height->setObjectName(QString::fromUtf8("height"));
        height->setMinimum(1);
        height->setMaximum(4000);
        height->setValue(500);

        horizontalLayout_2->addWidget(height);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(2, 1);

        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_2);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        angle = new QSpinBox(formLayoutWidget);
        angle->setObjectName(QString::fromUtf8("angle"));
        angle->setMinimum(1);
        angle->setMaximum(170);
        angle->setValue(100);

        horizontalLayout_3->addWidget(angle);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_3);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_6);

        background = new QDoubleSpinBox(formLayoutWidget);
        background->setObjectName(QString::fromUtf8("background"));
        background->setMaximum(1.000000000000000);
        background->setSingleStep(0.200000000000000);

        formLayout->setWidget(4, QFormLayout::FieldRole, background);

        groupBox = new QGroupBox(formLayoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));

        formLayout->setWidget(6, QFormLayout::SpanningRole, groupBox);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_7);

        Levels = new QSpinBox(formLayoutWidget);
        Levels->setObjectName(QString::fromUtf8("Levels"));
        Levels->setMinimum(1);
        Levels->setMaximum(3);

        formLayout->setWidget(7, QFormLayout::FieldRole, Levels);

        groupBox_2 = new QGroupBox(formLayoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));

        formLayout->setWidget(8, QFormLayout::SpanningRole, groupBox_2);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_8);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_9);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_10);

        label_11 = new QLabel(formLayoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_11);

        label_12 = new QLabel(formLayoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout->setWidget(14, QFormLayout::LabelRole, label_12);

        label_13 = new QLabel(formLayoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout->setWidget(15, QFormLayout::LabelRole, label_13);

        label_14 = new QLabel(formLayoutWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout->setWidget(16, QFormLayout::LabelRole, label_14);

        comboBox_2 = new QComboBox(formLayoutWidget);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("QColorConstants::Svg::blue");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        comboBox_2->addItem(icon, QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        formLayout->setWidget(11, QFormLayout::FieldRole, comboBox_2);

        comboBox_3 = new QComboBox(formLayoutWidget);
        comboBox_3->addItem(icon, QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        formLayout->setWidget(12, QFormLayout::FieldRole, comboBox_3);

        comboBox_4 = new QComboBox(formLayoutWidget);
        comboBox_4->addItem(icon, QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));

        formLayout->setWidget(13, QFormLayout::FieldRole, comboBox_4);

        comboBox_5 = new QComboBox(formLayoutWidget);
        comboBox_5->addItem(icon, QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));

        formLayout->setWidget(14, QFormLayout::FieldRole, comboBox_5);

        comboBox_6 = new QComboBox(formLayoutWidget);
        comboBox_6->addItem(icon, QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));

        formLayout->setWidget(15, QFormLayout::FieldRole, comboBox_6);

        comboBox_7 = new QComboBox(formLayoutWidget);
        comboBox_7->addItem(icon, QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));

        formLayout->setWidget(16, QFormLayout::FieldRole, comboBox_7);

        comboBox_1 = new QComboBox(formLayoutWidget);
        comboBox_1->addItem(icon, QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->addItem(QString());
        comboBox_1->setObjectName(QString::fromUtf8("comboBox_1"));

        formLayout->setWidget(10, QFormLayout::FieldRole, comboBox_1);

        label_15 = new QLabel(formLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_15);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_16 = new QLabel(formLayoutWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_4->addWidget(label_16);

        planthresh = new QDoubleSpinBox(formLayoutWidget);
        planthresh->setObjectName(QString::fromUtf8("planthresh"));
        planthresh->setMinimum(0.010000000000000);
        planthresh->setMaximum(1000.000000000000000);

        horizontalLayout_4->addWidget(planthresh);

        label_17 = new QLabel(formLayoutWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_4->addWidget(label_17);

        horizontalLayout_4->setStretch(1, 1);

        formLayout->setLayout(9, QFormLayout::FieldRole, horizontalLayout_4);

        label_18 = new QLabel(formLayoutWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_18);

        follow = new QCheckBox(formLayoutWidget);
        follow->setObjectName(QString::fromUtf8("follow"));
        follow->setChecked(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, follow);

        label_19 = new QLabel(formLayoutWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_19);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        ambient = new QDoubleSpinBox(formLayoutWidget);
        ambient->setObjectName(QString::fromUtf8("ambient"));
        ambient->setMaximum(1.000000000000000);
        ambient->setSingleStep(0.200000000000000);

        horizontalLayout_5->addWidget(ambient);

        label_20 = new QLabel(formLayoutWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_5->addWidget(label_20);


        formLayout->setLayout(5, QFormLayout::FieldRole, horizontalLayout_5);


        retranslateUi(DisplayOptions);

        Ok->setDefault(true);


        QMetaObject::connectSlotsByName(DisplayOptions);
    } // setupUi

    void retranslateUi(QWidget *DisplayOptions)
    {
        DisplayOptions->setWindowTitle(QCoreApplication::translate("DisplayOptions", "DisplayOptions", nullptr));
        Cancel->setText(QCoreApplication::translate("DisplayOptions", "Cancel", nullptr));
        Ok->setText(QCoreApplication::translate("DisplayOptions", "Ok", nullptr));
        label->setText(QCoreApplication::translate("DisplayOptions", "Render size", nullptr));
        label_2->setText(QCoreApplication::translate("DisplayOptions", "x", nullptr));
        label_3->setText(QCoreApplication::translate("DisplayOptions", "px", nullptr));
        label_4->setText(QCoreApplication::translate("DisplayOptions", "Field of view", nullptr));
        label_5->setText(QCoreApplication::translate("DisplayOptions", "Degrees", nullptr));
        label_6->setText(QCoreApplication::translate("DisplayOptions", "Background", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DisplayOptions", "Octrees", nullptr));
        label_7->setText(QCoreApplication::translate("DisplayOptions", "Levels render", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DisplayOptions", "Surface Type", nullptr));
        label_8->setText(QCoreApplication::translate("DisplayOptions", "Undetermined", nullptr));
        label_9->setText(QCoreApplication::translate("DisplayOptions", "Peak", nullptr));
        label_10->setText(QCoreApplication::translate("DisplayOptions", "Planar", nullptr));
        label_11->setText(QCoreApplication::translate("DisplayOptions", "Ridge", nullptr));
        label_12->setText(QCoreApplication::translate("DisplayOptions", "Pit", nullptr));
        label_13->setText(QCoreApplication::translate("DisplayOptions", "Saddle", nullptr));
        label_14->setText(QCoreApplication::translate("DisplayOptions", "Valley", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_2->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_2->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_2->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_2->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_2->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_2->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_2->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_3->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_3->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_3->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_3->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_3->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_3->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_3->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_3->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        comboBox_4->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_4->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_4->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_4->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_4->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_4->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_4->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_4->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_4->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_4->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_4->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        comboBox_5->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_5->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_5->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_5->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_5->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_5->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_5->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_5->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_5->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_5->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_5->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        comboBox_6->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_6->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_6->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_6->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_6->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_6->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_6->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_6->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_6->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_6->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_6->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_6->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        comboBox_7->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_7->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_7->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_7->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_7->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_7->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_7->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_7->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_7->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_7->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_7->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_7->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_7->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        comboBox_1->setItemText(0, QCoreApplication::translate("DisplayOptions", "Red", nullptr));
        comboBox_1->setItemText(1, QCoreApplication::translate("DisplayOptions", "Green", nullptr));
        comboBox_1->setItemText(2, QCoreApplication::translate("DisplayOptions", "Blue", nullptr));
        comboBox_1->setItemText(3, QCoreApplication::translate("DisplayOptions", "Cyan", nullptr));
        comboBox_1->setItemText(4, QCoreApplication::translate("DisplayOptions", "Magenta", nullptr));
        comboBox_1->setItemText(5, QCoreApplication::translate("DisplayOptions", "Yellow", nullptr));
        comboBox_1->setItemText(6, QCoreApplication::translate("DisplayOptions", "DarkRed", nullptr));
        comboBox_1->setItemText(7, QCoreApplication::translate("DisplayOptions", "Coral", nullptr));
        comboBox_1->setItemText(8, QCoreApplication::translate("DisplayOptions", "CornflowerBlue", nullptr));
        comboBox_1->setItemText(9, QCoreApplication::translate("DisplayOptions", "DarkOrange", nullptr));
        comboBox_1->setItemText(10, QCoreApplication::translate("DisplayOptions", "LavenderBlush", nullptr));
        comboBox_1->setItemText(11, QCoreApplication::translate("DisplayOptions", "LightBlue", nullptr));
        comboBox_1->setItemText(12, QCoreApplication::translate("DisplayOptions", "Black", nullptr));

        label_15->setText(QCoreApplication::translate("DisplayOptions", "Planar Threshold", nullptr));
        label_16->setText(QCoreApplication::translate("DisplayOptions", "1/", nullptr));
        label_17->setText(QCoreApplication::translate("DisplayOptions", "/maxBound", nullptr));
        label_18->setText(QCoreApplication::translate("DisplayOptions", "Light", nullptr));
        follow->setText(QCoreApplication::translate("DisplayOptions", "Follow Camera (SpaceBar)", nullptr));
        label_19->setText(QCoreApplication::translate("DisplayOptions", "Ambient light", nullptr));
        label_20->setText(QCoreApplication::translate("DisplayOptions", "* Background", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DisplayOptions: public Ui_DisplayOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYOPTIONS_H
