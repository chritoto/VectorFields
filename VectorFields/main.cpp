#include "MainWindows.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setWindowIcon(QIcon("./images/icon.png"));
	MainWindows w;
	w.show();
	return a.exec();
}
