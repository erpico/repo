#pragma once

#include "GuiLib.h"

#include "include\cef_client.h"
#include "include\base\cef_lock.h"
#include "include\wrapper\cef_helpers.h"
#include "include\cef_app.h"
#include "include\cef_sandbox_win.h"

class GUILIB_API ClientHandler : public CefClient,
                                 public CefDisplayHandler,
                                 public CefLifeSpanHandler,
                                 public CefLoadHandler,
                                 public CefRequestHandler
{
public:
   // Implement this interface to receive notification of ClientHandler
   // events. The methods of this class will be called on the main thread.
   class Delegate 
   {
   public:
      // Called when the browser is created.
      virtual void OnBrowserCreated(CefRefPtr<CefBrowser> browser) = 0;

      // Called when the browser is closing.
      virtual void OnBrowserClosing(CefRefPtr<CefBrowser> browser) = 0;

      // Called when the browser has been closed.
      virtual void OnBrowserClosed(CefRefPtr<CefBrowser> browser) = 0;

      // Set the window URL address.
      virtual void OnSetAddress(std::string const & url) = 0;

      // Set the window title.
      virtual void OnSetTitle(std::string const & title) = 0;

      // Set fullscreen mode.
      virtual void OnSetFullscreen(bool const fullscreen) = 0;

      // Set the loading state.
      virtual void OnSetLoadingState(bool const isLoading,
         bool const canGoBack,
         bool const canGoForward) = 0;

   protected:
      virtual ~Delegate() {}
   };

 public:
   ClientHandler();//Delegate* delegate);
   ~ClientHandler() {};

  void CreateBrowser(CefWindowInfo const & info, CefBrowserSettings const & settings, CefString const & url);  

  // CefClient methods:
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override { return this; }
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override { return this; }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override { return this; }
  virtual CefRefPtr<CefRequestHandler> GetRequestHandler() { return this; }

  // CefDisplayHandler methods:
  virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) override;
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) override;
  virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen) override;

  // CefLifeSpanHandler methods:
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;  

  virtual bool GetAuthCredentials( CefRefPtr< CefBrowser > browser, CefRefPtr< CefFrame > frame, bool isProxy, const CefString& host, int port, const CefString& realm, const CefString& scheme, CefRefPtr< CefAuthCallback > callback ) override;  

  // CefLoadHandler methods:
  virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
     bool isLoading,
     bool canGoBack,
     bool canGoForward) override;

  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl) override;

    bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                CefProcessId source_process,
                                CefRefPtr<CefProcessMessage> message) OVERRIDE;


  // This object may outlive the Delegate object so it's necessary for the
  // Delegate to detach itself before destruction.
  void DetachDelegate();

  CefRefPtr<CefBrowser> GetBrowser() { return m_browser; }

  //CChromiumTestDlg* m_pMainDlg;
  HWND m_hMainWnd;
  int m_BrowserId;
  int m_credTry;

private:
  
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(ClientHandler);
  // Include the default locking implementation.
  IMPLEMENT_LOCKING(ClientHandler);

private:
   Delegate* m_delegate;
   CefRefPtr<CefBrowser> m_browser;
};

class GUILIB_API MyCefApp : public CefApp, 
                            public CefRenderProcessHandler
{
public:
  MyCefApp() {};
  ~MyCefApp() {};

private:
  void OnContextCreated(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    CefRefPtr<CefV8Context> context) override;

private:
  
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(MyCefApp);
  // Include the default locking implementation.
  IMPLEMENT_LOCKING(MyCefApp);
};

class GUILIB_API ErRequestContextHandler : public CefRequestContextHandler
{
public:
   ErRequestContextHandler(const std::string &_strWorkPath);
   ~ErRequestContextHandler(){};
   CefRefPtr<CefCookieManager> GetCookieManager() OVERRIDE{         
      return cookieManager;
   }
private:
   // Include the default reference counting implementation.
   IMPLEMENT_REFCOUNTING(ErRequestContextHandler);
   CefRefPtr<CefCookieManager> cookieManager;
};

class GUILIB_API myClientHandler : public CefClient
{
  public:
    myClientHandler()  {}
    ~myClientHandler() {}

  protected:
    IMPLEMENT_REFCOUNTING(myClientHandler);
};

class GUILIB_API MyV8Handler : public CefV8Handler {
public:
  MyV8Handler() {}

  virtual bool Execute(const CefString& name,
                       CefRefPtr<CefV8Value> object,
                       const CefV8ValueList& arguments,
                       CefRefPtr<CefV8Value>& retval,
                       CefString& exception) OVERRIDE {
    if (name == "myfunc") {
      // Return my string value.
      retval = CefV8Value::CreateString("My Value!");
      return true;
    }

    // Function does not exist.
    return false;
  }

  // Provide the reference counting implementation for this class.
  IMPLEMENT_REFCOUNTING(MyV8Handler);
};

// Global var
//extern CefRefPtr<ClientHandler> g_handler;