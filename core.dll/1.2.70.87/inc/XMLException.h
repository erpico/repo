/************************************************************************
 *  created:    27.6.2007  11:24
 *  filename:   XMLException.h
 *  author:     Kapralov A.
 *
 *  purpose:    CXMLException - ����� ���������� ��� ������� XML.
 *  version:    1.0
 ************************************************************************/

#ifndef __XMLEXCEPTION_H__
#define __XMLEXCEPTION_H__

#include "Core.h"

#include "MyException.h"

// ���������� ��� ������ � XML.
// Author: Kapralov A.
class CORE_API CXMLException : public CMyException
{
public:
    // �����������.
    CXMLException();
    // �����������.
    // _message - ��������� �� ������.
    CXMLException(const char * _message);
    // �����������.
    // _message - ��������� �� ������.
    CXMLException(CString & _message);
};

#endif // __XMLEXCEPTION_H__


