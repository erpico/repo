/*
 * WinUtils.h
 * 
 *
 * Капралов А.
 * 26.2.2013 12:36
 */

#ifndef __WINUTILS_H__
#define __WINUTILS_H__

#include "Core.h"

CORE_API LPSTR GetLastErrorMessage(DWORD dwLastError);
CORE_API std::string __stdcall ReadApplicationVersion();
CORE_API BOOL IsFleExist(const TCHAR *filename);
CORE_API std::string GetModuleDirectory();
CORE_API void CreateTrayIcon(HWND hWnd, UINT uID, HICON hIcon, const char *tip);
CORE_API void DeleteTrayIcon(HWND hWnd, UINT uID);
CORE_API void ShowTrayMessage(HWND hWnd, UINT uID, unsigned int icon, LPCTSTR title, LPCTSTR message, unsigned int timeout);
#endif // __WINUTILS_H__