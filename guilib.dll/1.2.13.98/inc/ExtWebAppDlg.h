/*
 * ExtWebAppDlg.h
 * 
 *
 * Капралов А.
 * 18.6.2013 17:05
 */
#ifndef __EXTWEBAPPDLG_H__
#define __EXTWEBAPPDLG_H__

#include "GuiLib.h"
#include "IEControl.h"
#include "Resource.h"

#include "AclLib/Ext.h"
#include "AclLib/AclObjects.h"

// ExtWebAppDlg dialog

class GUILIB_API ExtWebAppDlg : public CDialog {
  DECLARE_DYNAMIC(ExtWebAppDlg)

public:
  ExtWebAppDlg(const User *pUser, const ExtWebApp &webApp, UINT iconID, CWnd* pParent = NULL);   // standard constructor
  virtual ~ExtWebAppDlg();

private:
  const User *pUser;
  ExtWebApp webApp;
  UINT iconID;

public:
// Dialog Data
#ifdef GUILIB_EXPORTS
  enum { IDD = IDD_EXTWEBAPPDLG };
#endif

public:
  void CreateInternal(HWND hWndParent);

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
private:
  IEControl ieControl;

public:
  virtual BOOL OnInitDialog();
  virtual void PostNcDestroy();
  afx_msg void OnSize(UINT nType, int cx, int cy);
};

#endif // __EXTWEBAPPDLG_H__
