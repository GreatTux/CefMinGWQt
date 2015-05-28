#include "../cefqtclient/clientapp.h"


int main(int argc, char *argv[])
{
  CefMainArgs main_args((HINSTANCE)GetModuleHandle(0));
  
  CefRefPtr<ClientApp> app(new ClientApp);

  return CefExecuteProcess(main_args, app.get(), 0);
}
