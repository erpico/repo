#pragma once

#include "Resource.h"
// CCallWindowSel dialog

class CCallWindowSel : public CDialogEx
{
	DECLARE_DYNAMIC(CCallWindowSel)

public:
	CCallWindowSel(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCallWindowSel();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAKE_CALL_SELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstPhones;
	void AddPhone(const char* strPhone);
	void ClearPhones();
	virtual void OnCancel();
	virtual void OnOK();
};
