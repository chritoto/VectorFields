#pragma once

#include <QWidget>
#include "ui_DisplayOptions.h"
#include "Util.h"

#include <QDialog>

class DisplayOptions : public QDialog
{
	Q_OBJECT

public:
	DisplayOptions(QWidget *parent, const bool& follow, const float& angle, const Vec3f& size, const float& background, const float& ambient, const size_t& levels, const size_t& max, const float& planthresh, const std::vector<size_t> indexes);
	~DisplayOptions();
	bool change = false;
	Ui::DisplayOptions ui;

private slots:
	void on_Ok_clicked();
	void on_Cancel_clicked();

private:
	QColor colors[13] = { QColorConstants::Svg::red, //Colors for the color mapping of surface types
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
