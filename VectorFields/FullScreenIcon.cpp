#include "FullScreenIcon.h"

FullScreenIcon::FullScreenIcon(QWidget *parent)
	: QWidget(parent), Parent(parent)
{
	resize(20, 20);
	image = new QImage("./images/FullScreen.png");
	setCursor(QCursor(Qt::PointingHandCursor));
}

FullScreenIcon::~FullScreenIcon()
{
	delete image;
}

QSize FullScreenIcon::sizeHint() const
{
	return QSize(20,20);
}

void FullScreenIcon::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.drawImage(QPoint(0, 0), image->scaled(size(), Qt::KeepAspectRatio));
}

void FullScreenIcon::mousePressEvent(QMouseEvent* event)
{
	emit clicked();
}
