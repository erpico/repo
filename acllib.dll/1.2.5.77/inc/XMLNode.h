/************************************************************************
*  created:    27.6.2007  11:06
*  filename:   XMLNode.h
*  author:     Kapralov A.
*
*  purpose:    CXMLNode - ����� ���� XML-���������.
*  version:    1.0
************************************************************************/

#ifndef __XMLNODE_H__
#define __XMLNODE_H__

#include "Core.h"

#include <map>
#include <list>
#include "afxmt.h"

#pragma warning(disable: 4192) // warning C4192: automatically excluding 'ISequentialStream' while importing type library 'MSXML6.dll'
#import "MSXML6.dll" named_guids 
//using namespace MSXML2;

// ���� XML-���������.
// Author: Kapralov A.
class CORE_API CXMLNode
{
public:
  static CCriticalSection g_CritCoOperation;
  // �����������.
  CXMLNode();
  // �����������.
  // _pNode - ���� XML-���������.
  CXMLNode(MSXML2::IXMLDOMNodePtr _pNode);
  CXMLNode& operator=(const CXMLNode& src);

  // ����������.
  ~CXMLNode();

  //�������� �� ������ ����
  bool IsOk()
  {
    return (m_pNode != NULL);
  }

  // ��������������� ���� � ��� ���������� �������������.
  // _string - �������������� ������.
  void ToString(CString & _string);

  // �������� ��� ����.
  // _name - �������������� ������.
  bool CXMLNode::GetName(CString & _name);

  // ����� �� ������ ������� �������� ���� � ��������������� ������.
  // _name - ��� ��������� ����.
  // ����������: true - ���� �������� ���� ������������, false - �����.
  bool HasChild(const char * _name);

  // �������� �������� ���� � �������� ������.
  // _szName - ��� ����.
  // ����������: �������� ���� � �������� ������.
  // ������ ����, ���� ��������� ���� � ����� ������ 
  // �� ����������.
  CXMLNode GetChildNode(const char * _szName);

  // ����������� �������� ���� � �������� ������.
  // ����������: �������������� ����.
  // ������ ����, ���� ��������� ������.
  CXMLNode AppendChild(const char * _szName);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  bool AppendChild(const char * _name, const char * _value);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  bool AppendChild(const char * _name, long _value);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  bool AppendChild(const char * _name, unsigned long _value);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  bool AppendChild(const char * _name, int _value);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  bool AppendChild(const char * _name, long long _value);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  // _format - ������ ������ (����� �� ��� � � printf, ������ ��� 
  // ������� ����, ��������, "1.2").
  bool AppendChild(const char * _name, float _value, const char * _format = NULL);
  // ����������� �������� ���� � �������� ������ � ���������.
  // _name - ��� ����.
  // _value - ��������.
  // _format - ������ ������ (����� �� ��� � � printf, ������ ��� 
  // ������� ����, ��������, "1.2").
  bool AppendChild(const char * _name, double _value, const char * _format = NULL);
  // ����������� �������� ����.
  // _childNode - �������� ����.
  bool AppendChild(CXMLNode& _childNode);

  // �������� ��������� ���������� ����.
  // _buffer - �������������� ������.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� �����.
  bool GetTextContent(CString & _buffer);
  // �������� ���������� ���� � ���� ���� long.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� long.
  bool GetLongContent(long& value);
  // �������� ���������� ���� � ���� ���� unsigned long.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� unsigned long.
  bool GetUnsignedLongContent(unsigned long& value);
  // �������� ���������� ���� � ���� ���� int.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� int.
  bool GetIntContent(int& value);
  // �������� ���������� ���� � ���� ���� int64.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� int64.
  bool GetInt64Content(long long& value);
  // �������� ���������� ���� � ���� ���� float.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� float.
  bool GetFloatContent(float& value);
  // �������� ���������� ���� � ���� ���� double.
  // ����������: false, ���� ���� �� ����� ���������� ��� 
  // ��� ���������� �� �������� ����� double.
  bool GetDoubleContent(double& value);

  // ������������� ���������� ����.
  // _value - ��������.
  bool SetContent(const char * _value);
  // ������������� ���������� ����.
  // _value - ��������.
  bool SetContent(long _value);
  // ������������� ���������� ����.
  // _value - ��������.
  bool SetContent(int _value);
  // ������������� ���������� ����.
  // _value - ��������.
  bool SetContent(long long _value);
  // ������������� ���������� ����.
  // _value - ��������.
  // _format - ������ ������ (����� �� ��� � � printf, ������ ��� 
  // ������� ����, ��������, "1.2").
  bool SetContent(float _value, const char * _format = NULL);

  // ����� �� ������ ������� ������� � ��������������� ������.
  // _name - ��� ��������.
  // ����������: true - ���� ������� ������������, false - �����.
  bool HasAttribute(const char * _name);

  // �������� ��������� ������� ���� � �������� ������.
  // _name - ��� ��������.
  // _buffer - �������������� ������.
  bool GetDoubleAttribute(const char * _name, double& value);
  // �������� ��������� ������� ���� � �������� ������.
  // _name - ��� ��������.
  // value - ������������ �������� �������� ����.
  bool GetTextAttribute(const char * _name, CString & _buffer);
  // �������� ������� ���� � �������� ������ ���� int.
  // _name - ��� ��������.
  // value - ������������ �������� �������� ����.
  bool GetIntAttribute(const char * _name, int& value);
  // �������� ������� ���� � �������� ������ ���� long.
  // _name - ��� ��������.
  // value - ������������ �������� �������� ����.
  bool GetLongAttribute(const char * _name, long& value);
  // �������� ������� ���� � �������� ������ ���� int64.
  // _name - ��� ��������.
  // value - ������������ �������� �������� ����.
  bool GetInt64Attribute(const char * _name, long long& value);
  // �������� ������� ���� � �������� ������ ���� unsigned long.
  // _name - ��� ��������.
  // value - ������������ �������� �������� ����.
  bool GetUnsignedLongAttribute(const char * _name, unsigned long& value);

  // ������������� �������� �������� � �������� ������.
  // _name - ��� ��������.
  // _value - ����� �������� ��������.
  bool SetAttribute(const char * _name, const char * _value);
  // ������������� �������� �������� � �������� ������.
  // _name - ��� ��������.
  // _value - ����� �������� ��������.
  bool SetAttribute(const char * _name, double _value);
  // ������������� �������� �������� � �������� ������.
  // _name - ��� ��������.
  // _value - ����� �������� ��������.
  bool SetAttribute(const char * _name, int _value);
  // ������������� �������� �������� � �������� ������.
  // _name - ��� ��������.
  // _value - ����� �������� ��������.
  bool SetAttribute(const char * _name, long long _value);
  // ������������� �������� �������� � �������� ������.
  // _name - ��� ��������.
  // _value - ����� �������� ��������.
  bool SetAttribute(const char * _name, long _value);
  // ������������� �������� �������� � �������� ������.
  // _name - ��� ��������.
  // _value - ����� �������� ��������.
  bool SetAttribute(const char * _name, unsigned long _value);

  // �������� ����� �������� �����. � ����� ������ �������� ��� ����, 
  // � ��������� ��� ����.
  // _nodeMap - �������������� �����.
  bool GetChildsMap(std::map<CString, CXMLNode > & _nodeMap);
  // �������� ������ �������� �����. 
  // _nodeList - �������������� ������.
  bool GetChildsList(std::list<CXMLNode > & _nodeList);

protected:

  // ���������� ������������ ����.
  MSXML2::IXMLDOMNodePtr GetDOMNode();
  // ������������� ������������ ���� ���������.
  void SetDOMNode(MSXML2::IXMLDOMNodePtr _pNode);

private:
  friend class CXMLDocument;
  //friend class std::map;

  // ������������ ��������� �� ���� XML-���������.
  MSXML2::IXMLDOMNodePtr m_pNode;

};



#endif // __XMLNODE_H__
