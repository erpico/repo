#pragma once

#include "ErpicoCTI/ACDClient.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TreeUpdater.h"
#include "SupervisorPanel.h"
#include "AgentsTab.h"
#include "CallGroupsTab.h"
#include "SupervisorChartDlg.h"
#include "afxbutton.h"

#include "Core/Runnable.h"
#include "GuiLib/ControlSplitter.h"
#include "GuiLib/ResizableLayout.h"





// SupervisorDialog dialog

class SUPERVISORPANEL_API SupervisorDialog : public CDialog, CResizableLayout
{
  DECLARE_DYNAMIC(SupervisorDialog)

public:
  SupervisorDialog(CWnd* pParent = NULL);   // standard constructor
  virtual ~SupervisorDialog();

// Dialog Data
  static const int IDD;

  HICON m_hIcon;

  HWND    m_hWndForSIPCall;
  UINT    m_nMsg;

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void PostNcDestroy();

  DECLARE_MESSAGE_MAP()  

  void HideAllTabsExceptOne(size_t idxToShow);
  void AlignTabs();

public:
  virtual BOOL OnInitDialog();
  virtual BOOL DestroyWindow();

  virtual void OnOK();
  virtual void OnCancel();
  
  void RefreshQueuesInfo(void);
  void SpySelectedCall(ESpyMode spyMode);
  void Refresh();
  void UpdateControls(void);
  void SetInfoForSIPCall(HWND hWnd, UINT nMsg);

private:
  CStatic m_gbTalks;
  CStatic m_gbQeues;
  CMFCButton m_btnSwitchTo;
  CMFCButton m_btnTap;
  CMFCButton m_btnSendTo;
  CMFCButton m_btnReset;

  CMFCButton m_btnHear;
  CMFCButton m_btnPrompter;
  CMFCButton m_btnCatch;
  CMFCButton m_btnShowScreen;
  CMFCButton m_btnMsg;
  CMFCButton m_btnCallAfter;
  CMFCButton m_btnCharts;

  CStatic m_stStatus;

  //CTreeCtrl m_cMembers;
  QueuesTreeCtrl m_treeQueues;
  
  CComboBox m_cOperatorsFilter;

  void initCurrentCallsControl(CListCtrl* listCurrentCalls);
  CListCtrl m_listCurrentCalls;
  CListCtrl m_listCurrentCallsEven;
  bool isCurrentCallsTwoLists_;
  std::vector<CCTICall> m_vctCurrentCalls;
  CTabCtrl m_cTabMembers;

  CControlSplitter m_vsplitter;
  CControlSplitter m_hsplitter;
  CControlSplitter m_vCurrentCallsSplitter;  

  // tab pages
  CAgentsTab m_tabAgents;
  CCallGroupsTab m_tabGroups;
  std::vector<CDialog*> m_vecMembersTabs;

  CImageList m_ilWndTree;

  typedef std::string QueueUniqueIdType;
  std::map<QueueUniqueIdType, HTREEITEM> m_mapQueueTreeItems;
  std::set<QueueUniqueIdType> m_setQueuesInTree;

  CACDClient &m_acdClient;
  CQueuesBranchUpdater m_treeQueuesUpdater;

  //  BOOL m_bAgentsOnly;
  CButton m_cbAgentsOnly;
  CButton m_cbTwoLists;
  CSupervisorChartDlg m_dlgCharts;

private:
  class Refresher : public IRunnable {
  private:
    SupervisorDialog *dlg;

  public:
    Refresher(SupervisorDialog *dlg);

  public:
    void Run();
  } refresher;
  
public:
  BOOL Create(CWnd* pParentWnd);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg void OnClose();
  afx_msg void OnBnClickedAgentsOnlyCheck();
  afx_msg void OnBnClickedSwitchto();
  afx_msg void OnTvnItemChangedTreeQueues(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedHear();
  afx_msg void OnBnClickedCharts();  
  afx_msg void OnLvnItemchangedCurrentCalls(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnBnClickedPrompter();
  afx_msg void OnNMDblclkCurrentCalls(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnCallsSpy();
  afx_msg void OnCallsWhisler();
  afx_msg void OnCallsBridge();  
  afx_msg void OnNMRClickCurrentCalls(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnTcnSelchangeTabAgentsGroups(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg LRESULT OnSplitMoved(WPARAM wp, LPARAM lp);
  void AlignControlsToSplitter();
  void RegisterSplitterRepositionControls();

  afx_msg void OnBnClickedTwoListsCheck();
  afx_msg void OnLvnItemActivateCurrentCalls(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnNMSetfocusCurrentCalls(NMHDR *pNMHDR, LRESULT *pResult);
};

DWORD WINAPI ExecuteRun(LPVOID lpParam);