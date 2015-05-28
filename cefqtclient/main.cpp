#include "application.h"
#include "mainwindow.h"

#include <windows.h>

#include "clientapp.h"
#include "clienthandler.h"

int main(int argc, char *argv[])
{
	// Cef initialization
	CefMainArgs main_args((HINSTANCE)GetModuleHandle(0));

	CefRefPtr<ClientApp> app(new ClientApp);

	CefSettings settings;
	CefString(&settings.browser_subprocess_path) = CefString("cefsubprocess.exe");
	settings.no_sandbox = true;

	CefInitialize(main_args, settings, app.get(), nullptr);

	// Qt initialization
	Application a(argc, argv);

	MainWindow w;
	w.show();

	// Run Qt event loop, handling cef event aswell
	a.run();

	CefShutdown();

	return 0;
}
