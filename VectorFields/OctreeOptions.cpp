#include "OctreeOptions.h"

OctreeOptions::OctreeOptions(QWidget *parent, const float& variation)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	ui.variation->setValue(variation);
}

OctreeOptions::~OctreeOptions()
{
}

void OctreeOptions::on_Cancel_clicked()
{
	close();
}

void OctreeOptions::on_Ok_clicked() {
	change = true;
	close();
}
