#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QFile>
#include "downloader.h"

namespace Ui
{
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = nullptr);
	~Widget();

private slots:
	// Slot for updating download progress
	void onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal);
	// Closing App function
	void closeDowloader();


private:
	// widget grid
	QGridLayout *gridLayout;
	// widget progress bar
	QProgressBar *downloadProgressBar;

	// widget text labels (showing time remaining of the download)
	QLabel *progressText1;
	QLabel *progressText2;
	QLabel *progressText3;
	QLabel *progressText4;
	QLabel *progressText5;
	QLabel *progressText6;


	// variables for previous Reply values of Receveid Bytes and elapsed download time
	qint64 prevTimerValue = 0;
	qint64 prevBytesReceivedValue = 0;

	// variable for skipping several network download progress repliyes (pause counter)
	int measPause = 0;

	// Downloader class
	Downloader  *downloader;
};

#endif // WIDGET_H

