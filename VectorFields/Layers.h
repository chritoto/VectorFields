#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindows.h"
#include "Util.h"
#include "VoxelBox.h"
#include "Scale.h"

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>

class Layers : public QWidget
{
	Q_OBJECT

public:
	Layers(QWidget *parent, const Ui::MainWindowsClass& p_ui, const size_t& p_num);
	~Layers();
	void clear();
	size_t setFrame(VoxelBox* p_Box, const int& p_index);
	void updateFrame(const size_t& pos);
	void updateFrame();
	size_t setAxis(const size_t& p_axis);
	void save(const QString& fileName);
	void setIndex(const int& p_index);
	void setScale(const bool& checked);
	void setColor(const int& p_color);
	void setLinear(const bool& lin);
	void setPower(const float& p_power);
	size_t setLayer(const int& p_layer);
	void setSize();

	Scale* scale; //the associated scale legend

private:
	
	QWidget* Parent;
	VoxelBox* Box;
	Vec3i size = Vec3i(400, 400, 0);
	QImage image = QImage(size.x, size.y, QImage::Format_RGB32);
	size_t axis = 2;
	Vec3i count;
	Vec3i countres;
	std::vector<std::vector<Voxel*>> voxels;
	size_t position = 0;
	Ui::MainWindowsClass ui;
	int index = 0;
	int color = 1;
	size_t layer = 1;
	size_t num = 0; //the id of the view to link to the scale
	
	size_t max; //max Voxel on selected axis
	float maxValue;
	unsigned char* buffer_;
	
	bool inverse = false;
	bool linear = false;
	float power = 0.5;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event);
};
