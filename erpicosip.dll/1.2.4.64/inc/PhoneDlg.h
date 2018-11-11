/*
 * PhoneDlg.h
 * 
 * Kapralov A.
 * 16.04.2014 16:09
 */

#ifndef __PHONEDLG_H__
#define __PHONEDLG_H__

#include "ErpicoSIP.h"
#include "VolumeDlg.h"
#ifdef ERPICOSIP_EXPORTS
#include "Resource.h"
#endif

#include <string>

class SipController;

// PhoneDlg dialog

class ERPICOSIP_API PhoneDlg : public CDialogEx {
  DECLARE_DYNAMIC(PhoneDlg)

public:
  PhoneDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~PhoneDlg();

#ifdef ERPICOSIP_EXPORTS
// Dialog Data
  enum { IDD = IDD_PHONE_DLG };
#endif
  enum CallMode { MAKE_CALL_MODE, INCOMING_CALL_MODE, TALK_MODE, REDIRECT_MODE };
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  
  DECLARE_MESSAGE_MAP()  

private:  
  SipController *sipController;
  CallMode mode_;
  bool m_bIsOpen;
  bool m_bIsInit;
  bool m_bAsPopup;
  bool m_bAutoAnswer;
  std::string m_strExt;
  std::string m_strCurrentNumber;

private:
  CFont charFont;
  CFont numberEditFontStatus;
  CFont numberEditFontNumber;
  CMFCButton char0Btn;
  CMFCButton char1Btn;
  CMFCButton char2Btn;
  CMFCButton char3Btn;
  CMFCButton char4Btn;
  CMFCButton char5Btn;
  CMFCButton char6Btn;
  CMFCButton char7Btn;
  CMFCButton char8Btn;
  CMFCButton char9Btn;
  CMFCButton charAsteriskBtn;
  CMFCButton charSharpBtn;
  CEdit numberEdit;
  CWnd* externalNumberEdit;
  CMFCButton callBtn;
  CMFCButton hangUpBtn;
  CMFCButton micBtn;
  CMFCButton volumeBtn;
  CMFCButton optionsBtn;
  CImageList m_imButtonsIcons;
  CProgressCtrl micSignalProgress;
  CProgressCtrl speakerSignalProgress;
  CWinThread* m_pThread;
  bool bStopThread;

  VolumeDlg volumeDlg;
  CallMode callMode_;
  bool numberEditStatusMode_;
  bool micOff_;
  void setCallMode(CallMode mode);
  void setNumberEditMode(bool statusMode);
  void setNumberEditText(CString text ,bool _bFocus = true);
public:
  void SetSipProperties(const char *id, const char *registrar, const char *realm, const char *user, const char *password);
  void SetExtNumber(const char* strNum) { m_strExt = strNum; }
  void UpdatePosVolumeConfig();
  void setExternalNumberEdit(CWnd* editControl);
  void setNumber(std::string number);
  bool call(std::string number, std::string& error);
  bool GetIsOpen();
  void SetIsOpen(bool _bVal);
  void initPhone();
  bool GetIsInit();
  void SetAsPopup(bool _bAsPopup);
  bool GetAsPopup();   
  bool GetAutoAnswer();
  void SetAutoAnswer(bool _bAutoAnswer);
  void SetCallBtnFocus();
  void PlayWaveFile();
  LPSTR loadAudioBlock(DWORD* blockSize);
  static UINT PlaySoundThread(LPVOID lParam);
  bool GetStopThread();  
  void SetStopThread(bool _bStopThread);
  
public:
  virtual BOOL OnInitDialog();
  virtual BOOL PreTranslateMessage(MSG *pMsg);
  void Create(CWnd* parentWnd);
  
public:
  afx_msg void OnCallClick();
  afx_msg void OnHangUpClick();
  afx_msg void OnDestroy();
  afx_msg void OnCharClick(UINT id);
  afx_msg void OnBnClickedVolume();
  afx_msg void OnBnClickedMic();
  afx_msg void OnBnClickedOptions();
  afx_msg void OnEnSetfocusNumberEdit();
  afx_msg void OnEnChangeNumberEdit();
  afx_msg void OnClose();
  afx_msg LRESULT OnRegStarted(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnRegStateChanged(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnCallStateChanged(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnIncomingCall(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnAutoAnswer(WPARAM wParam, LPARAM lParam);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
};

#endif // __PHONEDLG_H__
