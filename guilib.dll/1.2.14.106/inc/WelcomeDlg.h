#pragma once

#include "GuiLib.h"

#ifdef GUILIB_EXPORTS
#include "Resource.h"
#endif

#define WAITING_SECONDS 15

enum WelcomeDialogResult {
  WELCOME_ACCEPTED = 100,
  WELCOME_CANCELED = 101,
  WELCOME_PHONENUMBER_CONFIRMED = 102,
  WELCOME_PHONENUMBER_NOT_CONFIRMED = 103,
};

class GUILIB_API WelcomeDlg : public CDialogEx
{
  DECLARE_DYNAMIC(WelcomeDlg)
public:
  WelcomeDlg(CWnd* pParent = NULL);
  virtual ~WelcomeDlg();
  WelcomeDialogResult ShowDialog(const char* userName, const char* phoneNumber);
  CString GetPhoneNumber();
#ifdef GUILIB_EXPORTS
  enum { IDD = IDD_WELCOME_DLG };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual BOOL OnInitDialog();
  HICON m_hIcon;
private:
  CString acceptCode_;
  CString userName_;
  CString phoneNumber_;
  bool isVerifyMode_;

  int waitingSeconds_;

  CStatic descriptionStatic_;
  CStatic textStatic_;
  CEdit textEdit_;
  CButton confirmButton_;
  CButton beginButton_;

public:
  DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedConfirm();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnEnChangeEditWelcome();
  afx_msg void OnBnClickedBegin();
  afx_msg void OnBnClickedSupport();
};