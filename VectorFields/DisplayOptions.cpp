#include "DisplayOptions.h"


DisplayOptions::DisplayOptions(QWidget *parent, const bool& follow, const float& angle, const Vec3f& size, const float& background, const float& ambient, const size_t& levels, const size_t& max, const float& planthresh, const std::vector<size_t> indexes)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	ui.follow->setChecked(follow);
	ui.width->setValue(int(size.x));
	ui.height->setValue(int(size.y));
	ui.angle->setValue(int(angle));
	ui.background->setValue(background);
	ui.ambient->setValue(ambient);
	ui.Levels->setValue(levels);
	ui.Levels->setRange(1, max);
	ui.planthresh->setValue(float(1/planthresh));

	QComboBox* boxes[7] = { ui.comboBox_1,ui.comboBox_2,ui.comboBox_3,ui.comboBox_4,ui.comboBox_5,ui.comboBox_6,ui.comboBox_7 };
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 13; ++i) {
			boxes[j]->setItemData(i, colors[i], Qt::DecorationRole);
		}
		boxes[j]->setCurrentIndex(indexes[j]);
	}
}

DisplayOptions::~DisplayOptions()
{
}

void DisplayOptions::on_Cancel_clicked()
{
	close();
}

void DisplayOptions::on_Ok_clicked() {
	change = true;
	close();
}
