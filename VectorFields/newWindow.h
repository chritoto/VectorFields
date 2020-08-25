#pragma once

#include "rendererThread.h"

#include <QWidget>

class newWindow : public QWidget
{
	Q_OBJECT

public:
	newWindow(QWidget *parent = NULL);
	~newWindow();
	Renderer* renderer = nullptr;

private slots:
	void resizeEvent(QResizeEvent* event);
};
