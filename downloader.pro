

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DownloadHttp
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    downloader.cpp

HEADERS  += widget.h \
    downloader.h

FORMS    += widget.ui
