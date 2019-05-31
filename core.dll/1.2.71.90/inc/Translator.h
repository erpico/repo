// Translator.h: interface for the CTranslator class.
//
// Part of Digital Train Draw, a control system for model railroads.
//
// Coded by Isildur aka Gustau L. Castells
//
// Feel free to use this code. If you find it's useful for something...
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSLATOR_H__740AEC0F_7BA7_4472_BE04_8CA98BC4C487__INCLUDED_)
#define AFX_TRANSLATOR_H__740AEC0F_7BA7_4472_BE04_8CA98BC4C487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Core.h"

typedef struct TRANSLATION_TABLE {
  const char* szOriginal;
  const char* szTranslation;
} TRANSLATION_TABLE;

typedef struct TRANSLATION_LANGUAGE {
  const char* szLanguage;
  const TRANSLATION_TABLE* arrTable;
  int iId;
} TRANSLATION_LANGUAGE;

TRANSLATION_TABLE g_arrTranslation_RU[];
TRANSLATION_LANGUAGE g_arrLanguages[];

class CORE_API CTranslator  
{
public:
	CTranslator();
	virtual ~CTranslator();

	void TranslateDialog(CDialog *pDialog);
	void TranslateWindow(CWnd *pWnd);

	void TranslateMenu(CFrameWnd *pFrameWnd);
	void TranslateMenu(CMenu *pMenu);

  std::wstring GetTranslatedString(const wchar_t* strOriginal);
	const char* GetTranslatedString(const char* strOriginal);
	
	int GetCurrentLanguage() { return m_iCurrentLanguage; }
  void SetCurrentLanguage(int _iLanguage);

  void TranslateTabControl(CPropertySheet* pSheet);

  int GetLanguagesCount();
  TRANSLATION_LANGUAGE* GetLanguagesTable();

protected:
	int m_iCurrentLanguage;
  int m_iLanguagesCount;

private:
  void TranslateWindow_(CWnd *pWnd);
};

#endif // !defined(AFX_TRANSLATOR_H__740AEC0F_7BA7_4472_BE04_8CA98BC4C487__INCLUDED_)
