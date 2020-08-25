#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindows.h"
#include "Util.h"
#include "VoxelBox.h"

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>

class Renderer : public QWidget
{
	Q_OBJECT

public:
	Renderer(QWidget* parent, Ui::MainWindowsClass& p_ui);
	Renderer(QWidget* parent, Renderer& renderer);
	~Renderer();
	void clear();
	void setFrame(VoxelBox* p_Box);
	void updateFrame();
	void save(const QString& fileName);
	void setAxis(const size_t& p_Axis);
	void setEnable(const bool& val);
	void setLayer(const int& val);
	void setParameters();
	void setSurfaceType(const bool& surface);

	float angleView = 100;
	Vec3f size = Vec3f(500, 500, 0);

	Renderer* linked = nullptr;

	VoxelBox* Box = nullptr;
	float angleCamdelta = 0;
	float angleCamphi = 90;
	float angleLightdelta = 0;
	float angleLightphi = 90;
	float dist = 20;
	Vec3f offset = Vec3f(0, 0, 0);
	float dscreen;
	float aspectRatio = 1;
	float maxBound;
	bool lightFollow = false;
	Vec3f voxelDims;

	Vec3f Camera = Vec3f(sin(angleCamphi * PI / 180) * cos(angleCamdelta * PI / 180), sin(angleCamphi * PI / 180) * sin(angleCamdelta * PI / 180), cos(angleCamphi * PI / 180)) * dist;
	Vec3f d = Camera.normalize();
	Vec3f light = d;

	bool surfaceType = false;
	size_t colorMap[8] = { 7,2,0,1,5,3,12,7 };
	bool renderSeg = false;


protected:
	void keyPressEvent(QKeyEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void paintEvent(QPaintEvent* event) override;

private:

	QWidget* Parent;

	float zlight;

	unsigned char lightcolor[3] = { 255, 153, 51 };

	Vec3f xdir;
	Vec3f ydir;

	QImage image = QImage(size.x, size.y, QImage::Format_RGB32);
	QPoint origin;
	unsigned char* buffer_;
	int lastPos[2] = { 0,0 };
	Ui::MainWindowsClass* ui = nullptr;
	std::chrono::high_resolution_clock::time_point t1, t2;
	bool clicked = false;
	bool clickedLight = false;
	int lightSize = 5;
	int posx, posy;


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

	QStringList colorNames = colors[0].colorNames();
};
