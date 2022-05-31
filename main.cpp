#include <QApplication>
#include <QtWidgets>
#include "widget.h"
#include <iostream>
#include <direct.h>



int main(int argc, char *argv[])
{
	

	if (argc > 1)
	{
		// save path by deafualt
		if (argc < 4)
		{
			if (argc < 3) argv[2] = _getcwd( NULL, 0 );

			std::cout << "\nFile will be saved in " << argv[2] << "\n";

			// starting the Qt App with arguments from CLI interface
			QApplication app(argc, argv);
			Widget       myWidget;

			// setting widget size
			myWidget.resize(600, 78);
			// showing widget
			myWidget.show();

			return app.exec();
		}
		else
		{
			std::cout << "Too much arguments, Downloader.exe is now closing...\n";

		}
	}
	else
	{ 
		std::cout << "No file choosed to download, Downloader.exe is now closing...\n";
	}


	
}


