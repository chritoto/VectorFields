#include "newWindow.h"

newWindow::newWindow(QWidget *parent)
	: QWidget(parent)
{
}

newWindow::~newWindow()
{
	delete renderer;
}

void newWindow::resizeEvent(QResizeEvent* event)
{
	renderer->resize(size());
}
