#pragma once

#include "SupervisorPanel.h"
#include "ErpicoCTI/ACDClient.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TreeUpdater.h"
#include "GuiLib/ResizableLayout.h"

////////////////////////////////////////////////////////////////////////////
//
//
class SupervisorDialog;

//////////////////////////////////////////////////////////////////////////
//
// CAgentsTab dialog

class SUPERVISORPANEL_API CAgentsTab : public CDialogEx, CResizableLayout {
  DECLARE_DYNAMIC(CAgentsTab)

public:
  CAgentsTab(SupervisorDialog& dlgSupervisor);   // standard constructor
  virtual ~CAgentsTab();
  virtual BOOL PreTranslateMessage(MSG* pMsg);

  void Sync(std::list<SWCTIQueueInfo>& arrInfo);

  static const int IDD;

  enum EAction
  {
    eActionNone,
    eActionExpandAll,
    eActionCollapseAll
  };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  DECLARE_MESSAGE_MAP()
public:
  CTreeCtrl m_tree;
  CImageList m_ilWndTree;
  SupervisorDialog& m_dlgSupervisor;

  CMFCButton m_btnDisconnect;
  CMFCButton m_btnCall;
  CMFCButton m_btnScreen;
  CMFCButton m_btnMessage;
  CComboBox m_cbActions;  

  void DoTreeAction( EAction action );
  void DoCbSelectedAction();
  void UpdateControls(void);
  
  afx_msg void OnBnClickedCall();
  afx_msg void OnTvnSelchangedTreeAgents(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedDisconnect();	
  afx_msg void OnCbnSelchangeAgentsActions();	
  afx_msg void OnCbnCloseupAgentsActions();  
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnNMDblclkTreeAgents(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
};
