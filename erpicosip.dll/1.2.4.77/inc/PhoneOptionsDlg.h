#ifndef __PHONEOPTIONS_DLG_H__
#define __PHONEOPTIONS_DLG_H__

#include <MMSystem.h>
#ifdef ERPICOSIP_EXPORTS
#include "Resource.h"
#endif
#include "DSound.h"

BOOL CALLBACK DSEnumProc(LPGUID lpGUID, 
             LPCTSTR lpszDesc,
             LPCTSTR lpszDrvName, 
             LPVOID lpContext );

class PhoneOptionsDlg : public CDialogEx {
  DECLARE_DYNAMIC(PhoneOptionsDlg)
public:
  PhoneOptionsDlg(CWnd* pParent = NULL);
  virtual ~PhoneOptionsDlg();
#ifdef ERPICOSIP_EXPORTS
  enum { IDD = IDD_PHONE_OPTIONS_DLG };
#endif

  virtual BOOL OnInitDialog();

  bool Save();

  bool GetAutoAnswer()
  {
    return m_bAutoAnswer;
  }

  void SetAutoAnswer(bool _bAutoAnswer)
  {
    m_bAutoAnswer = _bAutoAnswer;
  }

protected:
  virtual void OnOK();
private:
  CComboBox* soundComboBox;
  CComboBox* micComboBox;
  CComboBox* ringComboBox;
  GUID micDevice_;
  GUID soundDevice_;
  UINT ringDevice_;
  bool m_bAutoAnswer;
  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnCbnSelchangeMicCombo();
  afx_msg void OnCbnSelchangeSoundCombo();
  afx_msg void OnCbnSelchangeRingCombo();
};
#endif