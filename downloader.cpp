#include "downloader.h"
#include <QCoreApplication>
#include <iostream>


Downloader::Downloader(QObject *parent)
	: QObject(parent)
{
	// Initializing network access manager
	manager = new QNetworkAccessManager();
	// connecting finish signal to the network reply proccesing function
	connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);

	// URL to download got via CLI
	QUrl url(__argv[1]); 
    // Initializing network request
	QNetworkRequest request;
	// add URL to request
	request.setUrl(url);

	// Initializing nework reply and send a request
	QNetworkReply *m_currentReply = manager->get(request);

	// connecting dowload progress data to downloader signal function
	connect(m_currentReply, &QNetworkReply::downloadProgress, this, &Downloader::updateDownloadProgress);
}


// A slot for network replyies processing
void Downloader::onResult(QNetworkReply *reply)
{
	// If an error received in reply
	if (reply->error())
	{
		// Reporting an error message and error info
		qDebug() << "ERROR";
		qDebug() << reply->errorString();
	}
	else
	{	
		std::string userURL = __argv[1]; // get the full user URL to extract filename

		std::string fileName = userURL.substr(userURL.rfind("/") + 1 );


		std::string userDirectory = __argv[2]; // get the user directory where to download file
	
		std::string fullFileNameStr = userDirectory + "\\" + fileName;

		char * fullFileName = new char[fullFileNameStr.length() + 1];
		std::strcpy(fullFileName, fullFileNameStr.c_str());

		

		// otherwise creating a new file in directory from CLI or default directory
		QFile *file = new QFile(fullFileName);
	
		// Creating new file or rewriting old one
		if (file->open(QFile::WriteOnly))
		{
			// getting all the data into the file
			file->write(reply->readAll());
			// closing file
			file->close();

			// sending a signal that download completed successfully
			emit onReady();
			qDebug() << "\nThe downloaded file was saved as '" << fullFileName << "'";

		}
		else
		{
			qDebug() << "\nError writing to file. File path '" << fullFileName << "'";
			emit onError();
		}
	}
}




