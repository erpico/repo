#ifndef __VOLUMEDLG_H__
#define __VOLUMEDLG_H__

#include "ErpicoSIP.h"
#ifdef ERPICOSIP_EXPORTS
#include "Resource.h"
#endif

class SipController;

class VolumeDlg : public CDialogEx {
  DECLARE_DYNAMIC(VolumeDlg)
public:
  VolumeDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~VolumeDlg();
  void setSipController(SipController *sipController);
#ifdef ERPICOSIP_EXPORTS
  enum { IDD = IDD_VOLUME_DLG };
#endif
  bool isActive();

  virtual BOOL OnInitDialog();  
  void ShowConfig(int x, int y);
  void HideConfig();
  void UpdatePosition(int x, int y);
  int getCurrentMicVolume();
 
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnDestroy();

protected:
  DECLARE_MESSAGE_MAP()
  virtual void DoDataExchange(CDataExchange* pDX);
  
private:
  CSliderCtrl micSlider;
  CSliderCtrl speakerSlider;
  bool isActive_;
  SipController *sipController_;
};

#endif // __VOLUMEDLG_H__