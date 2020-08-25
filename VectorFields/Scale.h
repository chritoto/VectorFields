#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindows.h"
#include "Util.h"

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QPixmap>
#include <QPainter>

class Scale : public QWidget
{
	Q_OBJECT

public:
	Scale(QWidget *parent, const Ui::MainWindowsClass& p_ui);
	~Scale();
	void clear();
	void setGrey(const bool& inv, const bool& lin, const float& power = 0.5);
	void setColor(const bool& inv, const bool& lin, const float& power = 0.5);

private:
	QWidget* Parent;
	Ui::MainWindowsClass ui;
	Vec3i size = Vec3i(300, 40, 0);
	QImage image = QImage(size.x, size.y, QImage::Format_RGB32);
	unsigned char* buffer_;

protected:
	void paintEvent(QPaintEvent* event) override;
};
