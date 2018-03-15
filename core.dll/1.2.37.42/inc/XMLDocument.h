/************************************************************************
*  created:    27.6.2007  10:58
*  filename:   XMLDocument.h
*  author:     Kapralov A.
*
*  purpose:    CXMLDocument - класс XML-документа.
*  version:    1.0
************************************************************************/

#ifndef __XMLDOCUMENT_H__
#define __XMLDOCUMENT_H__

#include "Core.h"

#include "XMLNode.h"

#include <comutil.h>
#include "afxmt.h"

// XML-документ.
// Author: Kapralov A.
class CORE_API CXMLDocument
{
public:
  // Конструктор.
  CXMLDocument();
  // Деструктор.
  ~CXMLDocument();

  bool CreateProcessingInstruction(const char *_strPart, const char *_strData);
  CXMLNode  GetProcessingInstruction(const char *_strPart);

  // Преобразовывает документ к строковому представлению.
  // _string - строка для вывода.
  void ToString(CString & _string, const char *_encoding = "UTF-8");

  // Загружает документ из строки.
  // _szSource - источник XML-документа.
  bool LoadFrom(const char * _szSource);

  // Получает корневой узел.
  CXMLNode GetRootNode();

  // Получает узел документа с заданным именем.
  // _szName - имя узла.
  // Возвращает: узел.
  CXMLNode GetNode(const char * _szName);

  // Создаёт узел с заданным именем.
  // _szName - имя узла.
  // Возвращает: созданный узел.
  // Выбрасывает: CXMLException, если произошла ошибка.
  CXMLNode CreateNode(const char * _szName);
  
  // Устанавливает корневой узел.
  // _szName - имя узла.
  // Возвращает: результирующий узел.
  // Выбрасывает: CXMLException, если произошла ошибка.
  CXMLNode SetRootNode(const char * _szName);
  // Устанавливает корневой узел.
  // _pNode - необходимый узел.
  // Выбрасывает: CXMLException, если произошла ошибка.
  bool SetRootNode(CXMLNode&  _pNode);

private:
  // Конструктор копии.
  CXMLDocument(const CXMLDocument & _anotherDocument);
  CXMLDocument & operator =(const CXMLDocument & _anotherDocument);

  class COMInitor
  {
  public:
     COMInitor();
    ~COMInitor();
  private:

     HRESULT m_hResult;
  } m_COMInitor;

  // XML-документ.
  MSXML2::IXMLDOMDocumentPtr m_pDoc;



};

#endif // __XMLDOCUMENT_H__
