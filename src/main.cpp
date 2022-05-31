#include <QApplication>
#include <QtWidgets>
#include "widget.h"
#include <iostream>
#include <direct.h>
#include <regex>



int main(int argc, char *argv[])
{
	

	if (argc > 1)
	{
		// save path by deafualt
		if (argc < 4)
		{	

			const std::regex urlPatCheck("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

			if (std::regex_match(argv[1], urlPatCheck))
			{
				if (argc < 3) argv[2] = _getcwd(NULL, 0);

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

				std::cout << "URL format is invalid, Downloader.exe is now closing...\n";

			}
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


