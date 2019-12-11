#include "downloader.h"



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
		// otherwise creating a new file in directory from CLI or default directory
		QFile *file = new QFile(__argv[2]);

	
		// Creating new file or rewriting old one
		if (file->open(QFile::WriteOnly))
		{
			// getting all the data into the file
			file->write(reply->readAll());
			// closing file
			file->close();
			qDebug() << "Downloading is completed";
			// sending a signal that download completed successfully
			emit onReady();
		}
	}
}




