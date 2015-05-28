#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QTimer>
#include "include/cef_app.h"

class Application: public QApplication
{
public:
	Application(int argc, char *argv[]):QApplication(argc,argv){}

	void run_cefloop()
	{
		QTimer* timer = new QTimer(this);
		QObject::connect(timer, &QTimer::timeout, this, &Application::cef_dowork, Qt::QueuedConnection);
		timer->start(30);
	}

	int run()
	{
		run_cefloop();
		return exec();
	}

public slots:
	void cef_dowork()
	{
		CefDoMessageLoopWork();
	}
};

#endif // APPLICATION_H
