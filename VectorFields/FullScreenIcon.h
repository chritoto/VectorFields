#pragma once

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>

class FullScreenIcon : public QWidget
{
	Q_OBJECT

public:
	FullScreenIcon(QWidget *parent);
	~FullScreenIcon();
	QSize sizeHint() const;

private:
	QImage* image = nullptr;
	QWidget Parent;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event);

signals:
	void clicked();
};
