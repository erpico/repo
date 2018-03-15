// AutoUpdater.h: interface for the CAutoUpdater class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
#define AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GuiLib.h"

#include <Wininet.h>

#include <map>

class GUILIB_API CAutoUpdater  {
public:
  CAutoUpdater();
  virtual ~CAutoUpdater();

  enum ErrorType { 
    Success                = 0, 
    InternetConnectFailure = 1, 
    InternetSessionFailure = 2, 
    ConfigDownloadFailure  = 3, 
    FileDownloadFailure    = 4, 
    NoExecutableVersion    = 5,
    UpdateRequired         = 6, 
    UpdateNotRequired      = 7, 
    UpdateNotComplete      = 8
  };

  ErrorType CheckForUpdate(LPCTSTR UpdateServerURL, std::map<CString, CString> &moduleVersions);	
  ErrorType Update(LPCTSTR UpdateServerURL, const std::map<CString, CString> &moduleVersions);
  void SetUpdateStatusFunc(void (*func)(void* statusControl, CString status, CString error),void* statusControl=NULL);
private:
  HINTERNET GetSession(CString &URL);
  void* statusControl_;
  void (*updateStatusFunc_)(void* statusControl, CString status, CString error);
  bool InternetOkay();
  bool DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize);
  bool DownloadFile(LPCTSTR url, LPCTSTR tempPath);
  bool DownloadFile(HINTERNET hSession, LPCTSTR url, LPCTSTR destination);
  
  int		CompareVersions(CString ver1, CString ver2);
  bool	IsDigits(CString text);
  CString GetExecutablePath();
  bool	Switch(CString executable, CString update, bool WaitForReboot);
public:
  static CString GetFileVersion(LPCTSTR file, CString* productName = 0);
private:
  HINTERNET hInternet;
};

#endif // !defined(AFX_AUTOUPDATER_H__227B2B21_B6AE_4164_B3A5_BFDAAF13D85D__INCLUDED_)
