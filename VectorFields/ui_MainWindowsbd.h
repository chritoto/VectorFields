/********************************************************************************
** Form generated from reading UI file 'MainWindows.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWS_H
#define UI_MAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowsClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *action_ply;
    QAction *action_stl;
    QAction *actionQuit;
    QAction *actionRenderer;
    QAction *actionWhat_s_new;
    QAction *action_Points;
    QAction *actionSurface_Variation;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *ImportPLY;
    QPushButton *ImportSTL;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QLabel *FileName;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QRadioButton *Octree;
    QDoubleSpinBox *doubleSpinBox_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QRadioButton *Size;
    QSpinBox *spinBox_3;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_4;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox;
    QRadioButton *Count;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QLabel *label_2;
    QPushButton *OctreeOptions;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_10;
    QSpinBox *MinPoints;
    QPushButton *Generate;
    QPushButton *Mesh;
    QPushButton *Spline;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_9;
    QLabel *points;
    QLabel *numPoints;
    QGridLayout *gridHistogram;
    QCustomPlot *customPlot;
    QSplitter *splitter;
    QGroupBox *renderBox;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridRenderer;
    QWidget *renderer;
    QSlider *GroupSlider;
    QHBoxLayout *horizontalLayout_7;
    QFormLayout *formLayout;
    QLabel *FPS_Label;
    QLabel *FPS;
    QVBoxLayout *verticalLayout_3;
    QPushButton *surfaceType;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *Segmentation;
    QComboBox *segType;
    QCheckBox *Isolate;
    QPushButton *DisplayOptions;
    QGroupBox *layerBox;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *Enable;
    QVBoxLayout *LayerFrame;
    QHBoxLayout *horizontalLayout_9;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QRadioButton *layerx;
    QRadioButton *layery;
    QRadioButton *layerz;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *Levels;
    QLabel *label_9;
    QSpinBox *layerSelect;
    QHBoxLayout *horizontalLayout_11;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_11;
    QWidget *Layer1;
    QVBoxLayout *verticalLayout_13;
    QWidget *Scale0;
    QHBoxLayout *horizontalLayout_10;
    QLabel *Min0;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Max0;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QWidget *Layer2;
    QVBoxLayout *verticalLayout_14;
    QWidget *Scale1;
    QHBoxLayout *horizontalLayout_13;
    QLabel *Min1;
    QSpacerItem *horizontalSpacer_3;
    QLabel *Max1;
    QVBoxLayout *verticalLayout_8;
    QSlider *Slider;
    QLabel *label_layer;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_14;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_15;
    QComboBox *Color;
    QCheckBox *Inverse;
    QGridLayout *gridLayout_4;
    QRadioButton *non_linear;
    QRadioButton *linear;
    QHBoxLayout *horizontalLayout_16;
    QLabel *labelpower;
    QDoubleSpinBox *power;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QGridLayout *gridLayout_2;
    QLabel *num_4;
    QLabel *voxz;
    QLabel *num_3;
    QLabel *voxx;
    QLabel *num_5;
    QLabel *voxy;
    QLabel *num;
    QLabel *num_2;
    QLabel *num_7;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuImport;
    QMenu *menuSave_image;
    QMenu *menuLayer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowsClass)
    {
        if (MainWindowsClass->objectName().isEmpty())
            MainWindowsClass->setObjectName(QString::fromUtf8("MainWindowsClass"));
        MainWindowsClass->resize(1437, 895);
        actionNew = new QAction(MainWindowsClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setEnabled(true);
        actionOpen = new QAction(MainWindowsClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setEnabled(true);
        actionSave = new QAction(MainWindowsClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(true);
        action_ply = new QAction(MainWindowsClass);
        action_ply->setObjectName(QString::fromUtf8("action_ply"));
        action_stl = new QAction(MainWindowsClass);
        action_stl->setObjectName(QString::fromUtf8("action_stl"));
        action_stl->setEnabled(true);
        actionQuit = new QAction(MainWindowsClass);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionRenderer = new QAction(MainWindowsClass);
        actionRenderer->setObjectName(QString::fromUtf8("actionRenderer"));
        actionWhat_s_new = new QAction(MainWindowsClass);
        actionWhat_s_new->setObjectName(QString::fromUtf8("actionWhat_s_new"));
        action_Points = new QAction(MainWindowsClass);
        action_Points->setObjectName(QString::fromUtf8("action_Points"));
        actionSurface_Variation = new QAction(MainWindowsClass);
        actionSurface_Variation->setObjectName(QString::fromUtf8("actionSurface_Variation"));
        centralWidget = new QWidget(MainWindowsClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMinimumSize);
        ImportPLY = new QPushButton(centralWidget);
        ImportPLY->setObjectName(QString::fromUtf8("ImportPLY"));

        horizontalLayout_5->addWidget(ImportPLY);

        ImportSTL = new QPushButton(centralWidget);
        ImportSTL->setObjectName(QString::fromUtf8("ImportSTL"));
        ImportSTL->setEnabled(true);

        horizontalLayout_5->addWidget(ImportSTL);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        FileName = new QLabel(centralWidget);
        FileName->setObjectName(QString::fromUtf8("FileName"));

        horizontalLayout_6->addWidget(FileName);

        horizontalLayout_6->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_4->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 3, 1, 1);

        Octree = new QRadioButton(centralWidget);
        Octree->setObjectName(QString::fromUtf8("Octree"));
        Octree->setChecked(true);

        gridLayout->addWidget(Octree, 5, 0, 1, 1);

        doubleSpinBox_3 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));
        doubleSpinBox_3->setMinimum(0.010000000000000);
        doubleSpinBox_3->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox_3, 2, 3, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setMinimum(0.010000000000000);
        doubleSpinBox_2->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox_2, 2, 2, 1, 1);

        Size = new QRadioButton(centralWidget);
        Size->setObjectName(QString::fromUtf8("Size"));
        Size->setChecked(false);

        gridLayout->addWidget(Size, 2, 0, 1, 1);

        spinBox_3 = new QSpinBox(centralWidget);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setMinimum(1);
        spinBox_3->setMaximum(100000);

        gridLayout->addWidget(spinBox_3, 3, 3, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 2, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMinimum(0.010000000000000);
        doubleSpinBox->setMaximum(100000.000000000000000);

        gridLayout->addWidget(doubleSpinBox, 2, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        spinBox_4 = new QSpinBox(centralWidget);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setMinimum(2);
        spinBox_4->setMaximum(15);

        gridLayout->addWidget(spinBox_4, 5, 1, 1, 1);

        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(100000);

        gridLayout->addWidget(spinBox, 3, 1, 1, 1);

        Count = new QRadioButton(centralWidget);
        Count->setObjectName(QString::fromUtf8("Count"));

        gridLayout->addWidget(Count, 3, 0, 2, 1);

        spinBox_2 = new QSpinBox(centralWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(100000);

        gridLayout->addWidget(spinBox_2, 3, 2, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        OctreeOptions = new QPushButton(centralWidget);
        OctreeOptions->setObjectName(QString::fromUtf8("OctreeOptions"));

        gridLayout->addWidget(OctreeOptions, 5, 3, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_7->addWidget(label_10);

        MinPoints = new QSpinBox(centralWidget);
        MinPoints->setObjectName(QString::fromUtf8("MinPoints"));
        MinPoints->setMinimum(3);
        MinPoints->setMaximum(1000);
        MinPoints->setValue(8);

        verticalLayout_7->addWidget(MinPoints);

        Generate = new QPushButton(centralWidget);
        Generate->setObjectName(QString::fromUtf8("Generate"));
        Generate->setEnabled(false);

        verticalLayout_7->addWidget(Generate);

        verticalLayout_7->setStretch(2, 1);

        horizontalLayout_4->addLayout(verticalLayout_7);

        Mesh = new QPushButton(centralWidget);
        Mesh->setObjectName(QString::fromUtf8("Mesh"));
        Mesh->setEnabled(false);

        horizontalLayout_4->addWidget(Mesh);

        Spline = new QPushButton(centralWidget);
        Spline->setObjectName(QString::fromUtf8("Spline"));
        Spline->setEnabled(false);

        horizontalLayout_4->addWidget(Spline);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        points = new QLabel(centralWidget);
        points->setObjectName(QString::fromUtf8("points"));
        points->setEnabled(true);
        points->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        verticalLayout_9->addWidget(points);

        numPoints = new QLabel(centralWidget);
        numPoints->setObjectName(QString::fromUtf8("numPoints"));
        numPoints->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_9->addWidget(numPoints);


        horizontalLayout_4->addLayout(verticalLayout_9);

        gridHistogram = new QGridLayout();
        gridHistogram->setSpacing(6);
        gridHistogram->setObjectName(QString::fromUtf8("gridHistogram"));
        gridHistogram->setSizeConstraint(QLayout::SetDefaultConstraint);
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        gridHistogram->addWidget(customPlot, 0, 0, 1, 1);


        horizontalLayout_4->addLayout(gridHistogram);

        horizontalLayout_4->setStretch(5, 1);
        horizontalLayout_4->setStretch(7, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::Panel);
        splitter->setFrameShadow(QFrame::Raised);
        splitter->setLineWidth(1);
        splitter->setMidLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);
        renderBox = new QGroupBox(splitter);
        renderBox->setObjectName(QString::fromUtf8("renderBox"));
        renderBox->setEnabled(false);
        horizontalLayout_8 = new QHBoxLayout(renderBox);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_8->setContentsMargins(0, 0, -1, -1);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(9, 9, 9, 9);
        gridRenderer = new QGridLayout();
        gridRenderer->setSpacing(6);
        gridRenderer->setObjectName(QString::fromUtf8("gridRenderer"));
        renderer = new QWidget(renderBox);
        renderer->setObjectName(QString::fromUtf8("renderer"));
        renderer->setFocusPolicy(Qt::NoFocus);
        renderer->setAutoFillBackground(false);

        gridRenderer->addWidget(renderer, 0, 0, 1, 1);


        verticalLayout_4->addLayout(gridRenderer);

        GroupSlider = new QSlider(renderBox);
        GroupSlider->setObjectName(QString::fromUtf8("GroupSlider"));
        GroupSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(GroupSlider);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        FPS_Label = new QLabel(renderBox);
        FPS_Label->setObjectName(QString::fromUtf8("FPS_Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, FPS_Label);

        FPS = new QLabel(renderBox);
        FPS->setObjectName(QString::fromUtf8("FPS"));

        formLayout->setWidget(0, QFormLayout::FieldRole, FPS);


        horizontalLayout_7->addLayout(formLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        surfaceType = new QPushButton(renderBox);
        surfaceType->setObjectName(QString::fromUtf8("surfaceType"));

        verticalLayout_3->addWidget(surfaceType);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        Segmentation = new QCheckBox(renderBox);
        Segmentation->setObjectName(QString::fromUtf8("Segmentation"));

        horizontalLayout_17->addWidget(Segmentation);

        segType = new QComboBox(renderBox);
        segType->addItem(QString());
        segType->addItem(QString());
        segType->addItem(QString());
        segType->addItem(QString());
        segType->addItem(QString());
        segType->addItem(QString());
        segType->setObjectName(QString::fromUtf8("segType"));

        horizontalLayout_17->addWidget(segType);

        Isolate = new QCheckBox(renderBox);
        Isolate->setObjectName(QString::fromUtf8("Isolate"));

        horizontalLayout_17->addWidget(Isolate);


        verticalLayout_3->addLayout(horizontalLayout_17);


        horizontalLayout_7->addLayout(verticalLayout_3);

        DisplayOptions = new QPushButton(renderBox);
        DisplayOptions->setObjectName(QString::fromUtf8("DisplayOptions"));

        horizontalLayout_7->addWidget(DisplayOptions);


        verticalLayout_4->addLayout(horizontalLayout_7);

        verticalLayout_4->setStretch(0, 1);

        horizontalLayout_8->addLayout(verticalLayout_4);

        splitter->addWidget(renderBox);
        layerBox = new QGroupBox(splitter);
        layerBox->setObjectName(QString::fromUtf8("layerBox"));
        layerBox->setEnabled(false);
        layerBox->setFlat(false);
        layerBox->setCheckable(false);
        verticalLayout_5 = new QVBoxLayout(layerBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        Enable = new QCheckBox(layerBox);
        Enable->setObjectName(QString::fromUtf8("Enable"));
        Enable->setEnabled(false);

        verticalLayout_5->addWidget(Enable);

        LayerFrame = new QVBoxLayout();
        LayerFrame->setSpacing(6);
        LayerFrame->setObjectName(QString::fromUtf8("LayerFrame"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(layerBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        layerx = new QRadioButton(layerBox);
        layerx->setObjectName(QString::fromUtf8("layerx"));

        horizontalLayout_2->addWidget(layerx);

        layery = new QRadioButton(layerBox);
        layery->setObjectName(QString::fromUtf8("layery"));

        horizontalLayout_2->addWidget(layery);

        layerz = new QRadioButton(layerBox);
        layerz->setObjectName(QString::fromUtf8("layerz"));
        layerz->setChecked(true);

        horizontalLayout_2->addWidget(layerz);


        horizontalLayout_9->addLayout(horizontalLayout_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        Levels = new QHBoxLayout();
        Levels->setSpacing(6);
        Levels->setObjectName(QString::fromUtf8("Levels"));
        label_9 = new QLabel(layerBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        Levels->addWidget(label_9);

        layerSelect = new QSpinBox(layerBox);
        layerSelect->setObjectName(QString::fromUtf8("layerSelect"));
        layerSelect->setMinimum(1);

        Levels->addWidget(layerSelect);


        horizontalLayout_9->addLayout(Levels);


        LayerFrame->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_3 = new QGroupBox(layerBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_11 = new QVBoxLayout(groupBox_3);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        Layer1 = new QWidget(groupBox_3);
        Layer1->setObjectName(QString::fromUtf8("Layer1"));

        verticalLayout_11->addWidget(Layer1);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        Scale0 = new QWidget(groupBox_3);
        Scale0->setObjectName(QString::fromUtf8("Scale0"));

        verticalLayout_13->addWidget(Scale0);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        Min0 = new QLabel(groupBox_3);
        Min0->setObjectName(QString::fromUtf8("Min0"));
        Min0->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(Min0);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_2);

        Max0 = new QLabel(groupBox_3);
        Max0->setObjectName(QString::fromUtf8("Max0"));
        Max0->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(Max0);


        verticalLayout_13->addLayout(horizontalLayout_10);

        verticalLayout_13->setStretch(0, 1);

        verticalLayout_11->addLayout(verticalLayout_13);

        verticalLayout_11->setStretch(0, 9);
        verticalLayout_11->setStretch(1, 1);

        horizontalLayout_3->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(layerBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        Layer2 = new QWidget(groupBox_4);
        Layer2->setObjectName(QString::fromUtf8("Layer2"));
        Layer2->setEnabled(false);

        verticalLayout_6->addWidget(Layer2);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        Scale1 = new QWidget(groupBox_4);
        Scale1->setObjectName(QString::fromUtf8("Scale1"));

        verticalLayout_14->addWidget(Scale1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        Min1 = new QLabel(groupBox_4);
        Min1->setObjectName(QString::fromUtf8("Min1"));
        Min1->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(Min1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_3);

        Max1 = new QLabel(groupBox_4);
        Max1->setObjectName(QString::fromUtf8("Max1"));
        Max1->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(Max1);


        verticalLayout_14->addLayout(horizontalLayout_13);


        verticalLayout_6->addLayout(verticalLayout_14);

        verticalLayout_6->setStretch(0, 9);
        verticalLayout_6->setStretch(1, 1);

        horizontalLayout_3->addWidget(groupBox_4);


        horizontalLayout_11->addLayout(horizontalLayout_3);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        Slider = new QSlider(layerBox);
        Slider->setObjectName(QString::fromUtf8("Slider"));
        Slider->setEnabled(false);
        Slider->setMinimum(1);
        Slider->setPageStep(1);
        Slider->setOrientation(Qt::Vertical);

        verticalLayout_8->addWidget(Slider);

        label_layer = new QLabel(layerBox);
        label_layer->setObjectName(QString::fromUtf8("label_layer"));
        label_layer->setLayoutDirection(Qt::LeftToRight);
        label_layer->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_layer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_8->addItem(verticalSpacer);


        horizontalLayout_11->addLayout(verticalLayout_8);

        horizontalLayout_11->setStretch(0, 1);

        LayerFrame->addLayout(horizontalLayout_11);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        groupBox = new QGroupBox(layerBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        Color = new QComboBox(groupBox);
        Color->addItem(QString());
        Color->addItem(QString());
        Color->setObjectName(QString::fromUtf8("Color"));

        horizontalLayout_15->addWidget(Color);

        Inverse = new QCheckBox(groupBox);
        Inverse->setObjectName(QString::fromUtf8("Inverse"));

        horizontalLayout_15->addWidget(Inverse);


        verticalLayout_10->addLayout(horizontalLayout_15);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        non_linear = new QRadioButton(groupBox);
        non_linear->setObjectName(QString::fromUtf8("non_linear"));
        non_linear->setChecked(true);

        gridLayout_4->addWidget(non_linear, 0, 1, 1, 1);

        linear = new QRadioButton(groupBox);
        linear->setObjectName(QString::fromUtf8("linear"));
        linear->setChecked(false);

        gridLayout_4->addWidget(linear, 0, 0, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        labelpower = new QLabel(groupBox);
        labelpower->setObjectName(QString::fromUtf8("labelpower"));
        labelpower->setEnabled(false);

        horizontalLayout_16->addWidget(labelpower);

        power = new QDoubleSpinBox(groupBox);
        power->setObjectName(QString::fromUtf8("power"));
        power->setEnabled(false);
        power->setMaximum(20.000000000000000);
        power->setSingleStep(0.200000000000000);
        power->setValue(0.500000000000000);

        horizontalLayout_16->addWidget(power);


        gridLayout_4->addLayout(horizontalLayout_16, 1, 1, 1, 1);


        verticalLayout_10->addLayout(gridLayout_4);


        horizontalLayout->addLayout(verticalLayout_10);


        horizontalLayout_14->addWidget(groupBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_8 = new QLabel(layerBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_12->addWidget(label_8);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        num_4 = new QLabel(layerBox);
        num_4->setObjectName(QString::fromUtf8("num_4"));

        gridLayout_2->addWidget(num_4, 0, 4, 1, 1);

        voxz = new QLabel(layerBox);
        voxz->setObjectName(QString::fromUtf8("voxz"));
        voxz->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(voxz, 0, 5, 1, 1);

        num_3 = new QLabel(layerBox);
        num_3->setObjectName(QString::fromUtf8("num_3"));

        gridLayout_2->addWidget(num_3, 0, 2, 1, 1);

        voxx = new QLabel(layerBox);
        voxx->setObjectName(QString::fromUtf8("voxx"));
        voxx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(voxx, 0, 1, 1, 1);

        num_5 = new QLabel(layerBox);
        num_5->setObjectName(QString::fromUtf8("num_5"));

        gridLayout_2->addWidget(num_5, 0, 6, 1, 1);

        voxy = new QLabel(layerBox);
        voxy->setObjectName(QString::fromUtf8("voxy"));
        voxy->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(voxy, 0, 3, 1, 1);

        num = new QLabel(layerBox);
        num->setObjectName(QString::fromUtf8("num"));
        num->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(num, 0, 7, 1, 1);

        num_2 = new QLabel(layerBox);
        num_2->setObjectName(QString::fromUtf8("num_2"));

        gridLayout_2->addWidget(num_2, 0, 0, 1, 1);

        num_7 = new QLabel(layerBox);
        num_7->setObjectName(QString::fromUtf8("num_7"));

        gridLayout_2->addWidget(num_7, 0, 8, 1, 1);


        horizontalLayout_12->addLayout(gridLayout_2);


        horizontalLayout_14->addLayout(horizontalLayout_12);


        LayerFrame->addLayout(horizontalLayout_14);

        LayerFrame->setStretch(1, 1);

        verticalLayout_5->addLayout(LayerFrame);

        splitter->addWidget(layerBox);

        verticalLayout->addWidget(splitter);

        verticalLayout->setStretch(1, 1);
        MainWindowsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowsClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1437, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuImport = new QMenu(menuFile);
        menuImport->setObjectName(QString::fromUtf8("menuImport"));
        menuSave_image = new QMenu(menuFile);
        menuSave_image->setObjectName(QString::fromUtf8("menuSave_image"));
        menuLayer = new QMenu(menuSave_image);
        menuLayer->setObjectName(QString::fromUtf8("menuLayer"));
        MainWindowsClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowsClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowsClass->setStatusBar(statusBar);
        QWidget::setTabOrder(ImportPLY, ImportSTL);
        QWidget::setTabOrder(ImportSTL, Size);
        QWidget::setTabOrder(Size, doubleSpinBox);
        QWidget::setTabOrder(doubleSpinBox, doubleSpinBox_2);
        QWidget::setTabOrder(doubleSpinBox_2, doubleSpinBox_3);
        QWidget::setTabOrder(doubleSpinBox_3, Count);
        QWidget::setTabOrder(Count, spinBox);
        QWidget::setTabOrder(spinBox, spinBox_2);
        QWidget::setTabOrder(spinBox_2, spinBox_3);
        QWidget::setTabOrder(spinBox_3, Octree);
        QWidget::setTabOrder(Octree, spinBox_4);
        QWidget::setTabOrder(spinBox_4, OctreeOptions);
        QWidget::setTabOrder(OctreeOptions, DisplayOptions);
        QWidget::setTabOrder(DisplayOptions, Enable);
        QWidget::setTabOrder(Enable, Slider);
        QWidget::setTabOrder(Slider, Color);
        QWidget::setTabOrder(Color, Inverse);
        QWidget::setTabOrder(Inverse, layerx);
        QWidget::setTabOrder(layerx, layery);
        QWidget::setTabOrder(layery, layerz);
        QWidget::setTabOrder(layerz, power);
        QWidget::setTabOrder(power, linear);
        QWidget::setTabOrder(linear, non_linear);
        QWidget::setTabOrder(non_linear, layerSelect);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(menuSave_image->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(menuImport->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuImport->addAction(action_ply);
        menuImport->addAction(action_stl);
        menuSave_image->addAction(actionRenderer);
        menuSave_image->addAction(menuLayer->menuAction());
        menuLayer->addAction(action_Points);
        menuLayer->addAction(actionSurface_Variation);

        retranslateUi(MainWindowsClass);

        Color->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindowsClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowsClass)
    {
        MainWindowsClass->setWindowTitle(QCoreApplication::translate("MainWindowsClass", "3D vector field", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindowsClass", "New", nullptr));
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindowsClass", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindowsClass", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindowsClass", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindowsClass", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindowsClass", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_ply->setText(QCoreApplication::translate("MainWindowsClass", ".ply", nullptr));
        action_stl->setText(QCoreApplication::translate("MainWindowsClass", ".stl", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindowsClass", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindowsClass", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRenderer->setText(QCoreApplication::translate("MainWindowsClass", "Renderer", nullptr));
        actionWhat_s_new->setText(QCoreApplication::translate("MainWindowsClass", "What's new", nullptr));
        action_Points->setText(QCoreApplication::translate("MainWindowsClass", "#Points", nullptr));
        actionSurface_Variation->setText(QCoreApplication::translate("MainWindowsClass", "Surface Variation", nullptr));
        ImportPLY->setText(QCoreApplication::translate("MainWindowsClass", "Import .ply", nullptr));
        ImportSTL->setText(QCoreApplication::translate("MainWindowsClass", "Import .stl", nullptr));
        label->setText(QCoreApplication::translate("MainWindowsClass", "File:", nullptr));
        FileName->setText(QCoreApplication::translate("MainWindowsClass", "None", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindowsClass", "z", nullptr));
        Octree->setText(QCoreApplication::translate("MainWindowsClass", "Octree", nullptr));
        Size->setText(QCoreApplication::translate("MainWindowsClass", "Size", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindowsClass", "levels", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindowsClass", "y", nullptr));
        Count->setText(QCoreApplication::translate("MainWindowsClass", "Count", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindowsClass", "x", nullptr));
        label_2->setText(QString());
        OctreeOptions->setText(QCoreApplication::translate("MainWindowsClass", "Octrees Options", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindowsClass", "Min points Voxel:", nullptr));
        Generate->setText(QCoreApplication::translate("MainWindowsClass", "Generate", nullptr));
        Mesh->setText(QCoreApplication::translate("MainWindowsClass", "Generate Mesh", nullptr));
        Spline->setText(QCoreApplication::translate("MainWindowsClass", "Generate B-Spline", nullptr));
        points->setText(QCoreApplication::translate("MainWindowsClass", "#Points:", nullptr));
        numPoints->setText(QString());
        renderBox->setTitle(QCoreApplication::translate("MainWindowsClass", "Renderer", nullptr));
        FPS_Label->setText(QCoreApplication::translate("MainWindowsClass", "FPS:", nullptr));
        FPS->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        surfaceType->setText(QCoreApplication::translate("MainWindowsClass", "Enable Surface Type", nullptr));
        Segmentation->setText(QCoreApplication::translate("MainWindowsClass", "Segmentation", nullptr));
        segType->setItemText(0, QCoreApplication::translate("MainWindowsClass", "Peak", nullptr));
        segType->setItemText(1, QCoreApplication::translate("MainWindowsClass", "Planar", nullptr));
        segType->setItemText(2, QCoreApplication::translate("MainWindowsClass", "Ridge", nullptr));
        segType->setItemText(3, QCoreApplication::translate("MainWindowsClass", "Pit", nullptr));
        segType->setItemText(4, QCoreApplication::translate("MainWindowsClass", "Saddle", nullptr));
        segType->setItemText(5, QCoreApplication::translate("MainWindowsClass", "Valley", nullptr));

        Isolate->setText(QCoreApplication::translate("MainWindowsClass", "Isolate Sections", nullptr));
        DisplayOptions->setText(QCoreApplication::translate("MainWindowsClass", "Display Options", nullptr));
        layerBox->setTitle(QCoreApplication::translate("MainWindowsClass", "Layer view", nullptr));
        Enable->setText(QCoreApplication::translate("MainWindowsClass", "Enable", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindowsClass", "Axis", nullptr));
        layerx->setText(QCoreApplication::translate("MainWindowsClass", "x", nullptr));
        layery->setText(QCoreApplication::translate("MainWindowsClass", "y", nullptr));
        layerz->setText(QCoreApplication::translate("MainWindowsClass", "z", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindowsClass", "Level:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindowsClass", "Number Points", nullptr));
        Min0->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        Max0->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindowsClass", "Surface Variation", nullptr));
        Min1->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        Max1->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        label_layer->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindowsClass", "Scale Options", nullptr));
        Color->setItemText(0, QCoreApplication::translate("MainWindowsClass", "Greyscale", nullptr));
        Color->setItemText(1, QCoreApplication::translate("MainWindowsClass", "Tint", nullptr));

        Inverse->setText(QCoreApplication::translate("MainWindowsClass", "Inverse", nullptr));
        non_linear->setText(QCoreApplication::translate("MainWindowsClass", "Non-Linear", nullptr));
        linear->setText(QCoreApplication::translate("MainWindowsClass", "Linear", nullptr));
        labelpower->setText(QCoreApplication::translate("MainWindowsClass", "Power:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindowsClass", "Selected:", nullptr));
        num_4->setText(QCoreApplication::translate("MainWindowsClass", "y", nullptr));
        voxz->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        num_3->setText(QCoreApplication::translate("MainWindowsClass", "x", nullptr));
        voxx->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        num_5->setText(QCoreApplication::translate("MainWindowsClass", "z", nullptr));
        voxy->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        num->setText(QCoreApplication::translate("MainWindowsClass", "0", nullptr));
        num_2->setText(QCoreApplication::translate("MainWindowsClass", "Voxel:", nullptr));
        num_7->setText(QCoreApplication::translate("MainWindowsClass", "Points", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindowsClass", "File", nullptr));
        menuImport->setTitle(QCoreApplication::translate("MainWindowsClass", "Import", nullptr));
        menuSave_image->setTitle(QCoreApplication::translate("MainWindowsClass", "Save image", nullptr));
        menuLayer->setTitle(QCoreApplication::translate("MainWindowsClass", "Layer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowsClass: public Ui_MainWindowsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWS_H
