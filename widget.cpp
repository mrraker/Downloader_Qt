#include  <QtWidgets>
#include "widget.h"
//global download timer
QElapsedTimer timeElapsed;


Widget::Widget(QWidget *parent)
	: QWidget(parent)

	//creating class objects
	, gridLayout(new QGridLayout)
	, downloadProgressBar (new QProgressBar)
	, progressText1 (new QLabel)
	, progressText2(new QLabel)
	, progressText3(new QLabel)
	, progressText4(new QLabel)
	, progressText5(new QLabel)
	, progressText6(new QLabel)

{
	QFont font("Times New Roman", 12, QFont::Normal);
	
	// setting the layout of child widgets
	gridLayout->setSpacing(5);
	gridLayout->setColumnMinimumWidth(0,1);
	gridLayout->setColumnMinimumWidth(1, 1);
	gridLayout->setColumnMinimumWidth(2, 1);
	gridLayout->setColumnMinimumWidth(3, 1);
	gridLayout->setColumnMinimumWidth(4, 1);
	gridLayout->setColumnMinimumWidth(5, 1);

	gridLayout->addWidget(progressText1, 0, 0, 1, 1);
	gridLayout->addWidget(progressText2, 0, 1, 1, 1);
	gridLayout->addWidget(progressText3, 0, 2, 1, 1);
	gridLayout->addWidget(progressText4, 0, 3, 1, 1);
	gridLayout->addWidget(progressText5, 0, 4, 1, 1);
	gridLayout->addWidget(progressText6, 0, 5, 1, 1);
	gridLayout->addWidget(downloadProgressBar,1,0,1,-1);

	// apply the grid layout of the widget 
	this->setLayout(gridLayout);
	
	// Starting timer
	timeElapsed.start();
	// Initializing dowloader
	downloader = new Downloader();
	
	// connecting the signal from dowloader with download prodress to widget function
	connect(downloader, &Downloader::updateDownloadProgress, this, &Widget::onUpdateProgress);

	// after download is completed sendind a signal to close funtiom
	connect(downloader, &Downloader::onReady, this, &Widget::closeDowloader);


}

// Widget destructor
Widget::~Widget()
{
	delete gridLayout;
	delete downloadProgressBar;
	delete progressText1;
	delete progressText2;
	delete progressText3;
	delete progressText4;
	delete progressText5;
	delete progressText6;

	gridLayout = nullptr;
	downloadProgressBar = nullptr;
	progressText1 = nullptr;
	progressText2 = nullptr;
	progressText3 = nullptr;
	progressText4 = nullptr;
	progressText5 = nullptr;
	progressText6 = nullptr;
}


void Widget::onUpdateProgress(qint64 bytesReceived, qint64 bytesTotal)
{
	// get the download progress to progress bar
	downloadProgressBar->setMaximum(bytesTotal/1024);
	downloadProgressBar->setValue(bytesReceived/1024);

	// remaining time for download is made only every 2 seconds (though a networkreply comes every 100 ms)
	// download speed is calculated by dividing receveid bytes on elapsed time since previous measurement (~2 seconds ago) 
	if (measPause % 20 == 0)
	{    
		// calculating seconds remained using the data from previous measuremnet
		qint64 secondsRemaining = (static_cast <qreal> (bytesTotal) - static_cast <qreal> (bytesReceived)) /
								((static_cast <qreal> (bytesReceived) - (static_cast <qreal> (prevBytesReceivedValue))) /
								((static_cast <qreal> (timeElapsed.elapsed()) - static_cast <qreal> (prevTimerValue)) / 1000));

		// saving current bytes downloaded and time elapsed values
		prevTimerValue = static_cast <qreal>(timeElapsed.elapsed());
		prevBytesReceivedValue = static_cast <qreal>(bytesReceived);

		//calculating remained minutes and hours
		qint64 minutesRemaining = secondsRemaining / 60;
		qint64 hoursRemaining = secondsRemaining / 3600;

		//removing remained time values above 59 for seconds and minutes
		qint64 minutesRemainingMod = minutesRemaining % 60;
		qint64 secondsRemainingMod = secondsRemaining % 60;
		

		// hiding labels with minutes and/or hour values if they are insignificant
		if (minutesRemainingMod == 0 && hoursRemaining ==0)
		{
			progressText1->setText("");
			progressText2->setText("");
			progressText3->setText("");
			progressText4->setText("");
		}
		else if (minutesRemainingMod != 0 && hoursRemaining == 0)
		{
			progressText1->setText("");
			progressText2->setText("");
			//displaying minutes remaining on widget
			QString textMinutesRemaining = QString::number(minutesRemainingMod);
			progressText3->setText(textMinutesRemaining);
			progressText4->setText(" minutes ");
		}
		else
		{	//displaying hours remaining on widget
			QString textHoursRemaining = QString::number(hoursRemaining);
			progressText1->setText(textHoursRemaining);
			progressText2->setText(" hours ");
			//displaying minutes remaining on widget
			QString textMinutesRemaining = QString::number(minutesRemainingMod);
			progressText3->setText(textMinutesRemaining);
			progressText4->setText(" minutes ");
		}

		//displaying seconds remaining on widget
		QString textSecondsRemaining = QString::number(secondsRemainingMod);
		progressText5->setText(textSecondsRemaining);
		progressText6->setText(" seconds remaining...");

	}
	// inreasing pause counter
	measPause++;
}


// closing downloader function
void Widget::closeDowloader()
{
	QApplication::quit();
}