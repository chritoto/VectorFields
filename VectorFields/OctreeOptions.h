#pragma once

#include <QDialog>
#include "ui_OctreeOptions.h"
#include "Util.h"

class OctreeOptions : public QDialog
{
	Q_OBJECT

public:
	OctreeOptions(QWidget *parent, const float& variation);
	~OctreeOptions();
	bool change = false;
	Ui::OctreeOptions ui;

private slots:
	void on_Ok_clicked();
	void on_Cancel_clicked();

private:
};
