/************************************************************************
*  created:    27.6.2007  10:58
*  filename:   XMLDocument.h
*  author:     Kapralov A.
*
*  purpose:    CXMLDocument - ����� XML-���������.
*  version:    1.0
************************************************************************/

#ifndef __XMLDOCUMENT_H__
#define __XMLDOCUMENT_H__

#include "Core.h"

#include "XMLNode.h"

#include <comutil.h>
#include "afxmt.h"

// XML-��������.
// Author: Kapralov A.
class CORE_API CXMLDocument
{
public:
  // �����������.
  CXMLDocument();
  // ����������.
  ~CXMLDocument();

  bool CreateProcessingInstruction(const char *_strPart, const char *_strData);
  CXMLNode  GetProcessingInstruction(const char *_strPart);

  // ��������������� �������� � ���������� �������������.
  // _string - ������ ��� ������.
  void ToString(CString & _string, const char *_encoding = "UTF-8");

  // ��������� �������� �� ������.
  // _szSource - �������� XML-���������.
  bool LoadFrom(const char * _szSource);

  // �������� �������� ����.
  CXMLNode GetRootNode();

  // �������� ���� ��������� � �������� ������.
  // _szName - ��� ����.
  // ����������: ����.
  CXMLNode GetNode(const char * _szName);

  // ������ ���� � �������� ������.
  // _szName - ��� ����.
  // ����������: ��������� ����.
  // �����������: CXMLException, ���� ��������� ������.
  CXMLNode CreateNode(const char * _szName);
  
  // ������������� �������� ����.
  // _szName - ��� ����.
  // ����������: �������������� ����.
  // �����������: CXMLException, ���� ��������� ������.
  CXMLNode SetRootNode(const char * _szName);
  // ������������� �������� ����.
  // _pNode - ����������� ����.
  // �����������: CXMLException, ���� ��������� ������.
  bool SetRootNode(CXMLNode&  _pNode);

private:
  // ����������� �����.
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

  // XML-��������.
  MSXML2::IXMLDOMDocumentPtr m_pDoc;



};

#endif // __XMLDOCUMENT_H__
