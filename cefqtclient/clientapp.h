#ifndef CLIENTAPP_H_
#define CLIENTAPP_H_

#include "include/cef_app.h"

class ClientApp : public CefApp,
						public CefBrowserProcessHandler
{
public:
	ClientApp();

virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }
virtual void OnContextInitialized() override;

private:
	IMPLEMENT_REFCOUNTING(ClientApp)
};

#endif  // CLIENTAPP_H_
