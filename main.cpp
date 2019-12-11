#include <QApplication>
#include <QtWidgets>
#include "widget.h"




int main(int argc, char *argv[])
{	
	
	// save path by deafualt
	if (argc < 3) argv [2] = "D:/file.exe";

	// starting the Qt App with arguments from CLI interface
	QApplication app(argc, argv);
	Widget       myWidget;
     
	// setting widget size
	myWidget.resize(600, 78);
	// showing widget
	myWidget.show();

	return app.exec();
}
