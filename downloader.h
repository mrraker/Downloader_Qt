#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include <QCoreApplication>

class Downloader : public QObject
{
	Q_OBJECT
public:
	explicit Downloader(QObject *parent = nullptr);

signals:
	// A signal reported the dowload successfully completed
	void onReady();
	// A signal sent information about the progress of the download
	void updateDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

public slots:
	// A slot for network replyies processing
	void onResult(QNetworkReply *reply);
	
private:
	// Network access manager
	QNetworkAccessManager *manager;
	
};

#endif // DOWNLOADER_H
