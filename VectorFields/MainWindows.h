#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindows.h"

#include<QLayout>
#include<QDebug>
#include<QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QVector>
#include <QFileInfo>
#include <QPixmap>

#include "OctreeOptions.h"
#include "DisplayOptions.h"
#include "PointCloud.h"
#include "VoxelBox.h"
#include "rendererThread.h"
#include "Layers.h"
#include "Util.h"
#include "qcustomplot.h"
#include "FullScreenIcon.h"
#include "newWindow.h"
#include "meshRender.h"

class MainWindows : public QMainWindow
{
	Q_OBJECT

public:
	MainWindows(QWidget *parent = Q_NULLPTR);
	void displayMesh(unsigned char type);

private slots: //Interaction with the UI
	void on_ImportPLY_clicked();
	void on_ImportSTL_clicked();
	void on_Generate_clicked();
	void on_Spline_clicked();
	void on_Mesh_clicked();
	void on_action_ply_triggered();
	void on_action_stl_triggered();
	void on_actionRenderer_triggered();
	void on_action_Points_triggered();
	void on_actionSurface_Variation_triggered();
	void on_actionQuit_triggered();
	void on_actionSave_triggered();
	void on_actionOpen_triggered();
	void on_actionNew_triggered();
	void slider(int value);
	void setColor(int color);
	void on_layerx_clicked();
	void on_layery_clicked();
	void on_layerz_clicked();
	void on_Enable_clicked();
	void on_DisplayOptions_clicked();
	void on_surfaceType_clicked();
	void on_Segmentation_clicked();
	void on_Isolate_clicked();
	void sliderGroup(int value);
	void setSegType(int type);
	void on_OctreeOptions_clicked();
	void on_Inverse_clicked();
	void on_linear_clicked();
	void on_non_linear_clicked();
	void setPower(double power);
	void setLayer(int newLayer);
	void histogramClicked();
	void rendererClicked();
	void ExportMesh(QAction* action);
	void ExportSpline(QAction* action);
	void reloadOpenGL(int value);

	void splitter(int pos, int index);
	void resizeEvent(QResizeEvent* event);
	void showEvent(QShowEvent* event);

private:
	void initiateView();
	void createHistogram();
	

	Ui::MainWindowsClass ui;
	QString path = "";
	PointCloud points;
	VoxelBox* Voxels = nullptr;
	Renderer* renderer;
	Layers* layers1;
	Layers* layers2;
	int index = 0;
	double surfaceThreshold = 1e-7; //Threshold for creating childs in octree structure generation
	QCPBars* histogram = nullptr;
	std::vector<FullScreenIcon*> FSicons;
	QWidget* legendWidget;
	QGridLayout* legend = nullptr;
	QLabel* legendColors[7];
	QLabel* legendLabels[7];
	meshRender* meshwindow = nullptr;
	meshRender* meshSplinewindow = nullptr;

	QColor colors[13] = { QColorConstants::Svg::red, //Must be the same in DisplayOptions.h
	QColorConstants::Svg::green,
	QColorConstants::Svg::blue,
	QColorConstants::Svg::cyan,
	QColorConstants::Svg::magenta,
	QColorConstants::Svg::yellow,
	QColorConstants::Svg::darkred,
	QColorConstants::Svg::coral,
	QColorConstants::Svg::cornflowerblue,
	QColorConstants::Svg::darkorange,
	QColorConstants::Svg::lavenderblush,
	QColorConstants::Svg::lightblue,
	QColorConstants::Svg::black };
};
