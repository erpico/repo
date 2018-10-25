#pragma once

#include "GuiLib.h"

#ifdef GUILIB_EXPORTS
#include "Resource.h"
#endif
// CSupportDlg dialog

class GUILIB_API CSupportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSupportDlg)

public:
	CSupportDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSupportDlg();

// Dialog Data
#ifdef GUILIB_EXPORTS
	enum { IDD = IDD_SUPPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  CFont m_fntName;

public:
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
  afx_msg void OnBnClickedAmmy();
  afx_msg void OnClose();
  afx_msg void OnBnClickedCall();
  afx_msg void OnBnClickedSendReport();
  afx_msg void OnEnChangeReport();
  afx_msg void OnEnChangeMail();
  afx_msg void OnEnChangeName();
  afx_msg void OnEnChangePhone();
};
