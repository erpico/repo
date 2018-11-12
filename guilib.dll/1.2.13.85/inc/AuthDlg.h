#pragma once
#include "afxwin.h"

#include "GuiLib.h"
#ifdef GUILIB_EXPORTS
#include "Resource.h"
#endif
// CAuthDlg dialog

class GUILIB_API CAuthDlg : public CDialog
{
	DECLARE_DYNAMIC(CAuthDlg)

public:
	CAuthDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAuthDlg();

// Dialog Data
#ifdef GUILIB_EXPORTS
	enum { IDD = IDD_SIMPLE_AUTH };
#endif 
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual INT_PTR DoModal();
  CString m_Login;
  CString m_Password;
  virtual void OnOK();
};
