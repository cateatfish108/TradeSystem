#include "TradeSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TradeSystem w;
	w.show();
	return a.exec();
}
