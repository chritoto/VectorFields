#include "Scale.h"

Scale::Scale(QWidget *parent, const Ui::MainWindowsClass& p_ui)
	: QWidget(parent)
{
	Parent = parent;
	ui = p_ui;
	buffer_ = new unsigned char[4 * size.x * size.y];
	setAttribute(Qt::WA_StaticContents);
}

Scale::~Scale()
{
}

void Scale::clear()
{
	for (size_t x = 0; x < size.x; x++)
	{
		for (size_t y = 0; y < size.y; y++)
		{
			buffer_[4 * int(y * size.x + x)] = 0;
			buffer_[4 * int(y * size.x + x) + 1] = 0;
			buffer_[4 * int(y * size.x + x) + 2] = 0;
		}
	}
}

void Scale::setGrey(const bool& inv, const bool& lin, const float& power)
{
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			float intensity;
			if(inv) intensity = (1 - i / (float)size.x);
			else intensity = i / (float)size.x;

			if (!lin) intensity = pow(intensity, power);

			int value = int(intensity * 255);

			buffer_[4 * int(j * size.x + i)] = value;
			buffer_[4 * int(j * size.x + i) + 1] = value;
			buffer_[4 * int(j * size.x + i) + 2] = value;
		}
	}
	update();
}

void Scale::setColor(const bool& inv, const bool& lin, const float& power)
{
	for (int i = 0; i < size.x; i++) {
		for (int j = 0; j < size.y; j++) {
			float intensity;
			if (inv) intensity = (1 - i / (float)size.x);
			else intensity = i / (float)size.x;

			if (!lin) intensity = pow(intensity, power);

			QColor color;
			color.setHsv(int(intensity * 300), 255, 255);
			color.toRgb();
			
			buffer_[4 * int(j * size.x + i)] = color.red();
			buffer_[4 * int(j * size.x + i) + 1] = color.green();
			buffer_[4 * int(j * size.x + i) + 2] = color.blue();
		}
	}
	update();
}


void Scale::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	image = QImage(buffer_, size.x, size.y, QImage::Format_RGB32);
	
	painter.drawImage(QPoint(0, 0), image.scaledToWidth(Parent->size().width()));
}
