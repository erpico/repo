/*
 * AuthDialog.h
 * 
 *
 * Капралов А.
 * 12.3.2013 21:16
 */

#ifndef __AUTHDIALOG_H__
#define __AUTHDIALOG_H__

#include "GuiLib.h"

#include "Core/Thread.h"

#include "TransparentStatic2.h"
#include "ColorComboBox.h"

#include <list>
#ifdef GUILIB_EXPORTS
#include "Resource.h"
#include "ProgressRing.h"
#else
#include "GuiLib/ProgressRing.h"
#endif

class BaseCredentials
{
public:
  CString serverHost;
  CString userName;
};

// AuthDialog dialog

class GUILIB_API AuthDialog : public CDialog {
  DECLARE_DYNAMIC(AuthDialog)

public:
  class Authorizer {
  public:
    virtual int LogIn(const char *serverHost, const char *name, const char *password, bool saveCredentials, 
      bool autoLogOn) = 0;
  };

private:
  Authorizer *pAuthorizer;
  HICON hIcon;
  CString version;

public:
  void SetAuthorizer(Authorizer *pAuthorizer);
  void SetIcon(HICON hIcon);
  void SetVersion(const char *version);
  void SetBackgroundImage(HBITMAP hBmp);
  void SetChoosingLang(bool _bChoose);

private:
  class AuthThread : public CThread {
  private:
    AuthDialog *pParent;

  public:
    AuthThread(AuthDialog *pParent);

  protected: // IRunnable
    virtual void Run();
  } authThread;

private:
  ColorComboBox serverHostCmb;
  CString serverHost;
  std::list<CString> serverHosts;
  CString username;
  CString password;
  BOOL saveCredentials;
  BOOL autoLogOn;
  bool nextStartAutoLogOn;
  CStatic m_ctlBackground;
  HBITMAP m_hBkgrBmp;
  bool bChooseLanguage;

private:
  bool highlightServerHost;
  bool highlightUsername;
  bool highlightPassword;
  
  CBrush *pHighlightBkBrush;

  CTransparentStatic2 applicationNameLabel;
  CFont applicationNameLabelFont;
  CTransparentStatic2 statusLabel;
  CTransparentStatic2 errorLabel;
  CTransparentStatic2 versionLabel;
  CFont versionLabelFont;
  CFont statusLabelFont;
  CFont errorLabelFont;

//private:
//  CToolTipCtrl toolTip;

public:
  AuthDialog(CWnd* pParent = NULL);   // standard constructor
  virtual ~AuthDialog();
  virtual BOOL DestroyWindow();

public:
  void SetOptions(const std::list<CString> &serverHosts, 
      const CString &username, const CString &password, 
      bool saveCredentials, bool autoLogOn);
  
  void FillHistoryCredentials();
  void UpdateHistoryCredentials();
  void SaveNextStartAutoLogOn(bool autoLogOn);
  bool ReadNextStartAutoLogOn();
// Dialog Data
#ifdef GUILIB_EXPORTS
  enum { IDD = IDD_AUTH_DIALOG };
#endif

private:
  void EnableControls(BOOL bEnable);
  bool CheckData();  
  bool authResult_;
  CEvent* AuthEndEvent_;
  bool isModal_;  // Используется если без DoAuth(). Для совместимости
  std::vector<BaseCredentials> historyCredentials;
  
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  virtual INT_PTR DoModal();
  
  void setStatusText(const char *statusText, bool isError = false);  // Статус текущей операции инициализации 
  bool DoAuth();
  CWinThread* m_Thread;
  static UINT ThreadWindow(LPVOID lParam);
  int m_bHiddenMode;
  int m_bWeExists;
public:
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  afx_msg LRESULT OnLogInFinished(WPARAM wParam, LPARAM lParam);
  afx_msg void OnCbnSetFocusServerHostCombo();
  afx_msg void OnCbnKillFocusServerHostCombo();
  afx_msg void OnEnSetFocusUsername();
  afx_msg void OnEnKillFocusUsername();
  afx_msg void OnEnSetFocusPassword();
  afx_msg void OnEnKillFocusPassword();
  afx_msg void OnClose();
  afx_msg void OnSelchangeserverHostCmb();
  afx_msg void OnBnClickedSupport();
  afx_msg void OnCbnSelendokLanguage();
  
  ProgressRing m_progressRing;
  CComboBox m_ComboLang;
  CStatic m_LangImg;
};

#endif // __AUTHDIALOG_H__
