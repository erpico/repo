/************************************************************************
 *  created:    27.6.2007  11:24
 *  filename:   XMLException.h
 *  author:     Kapralov A.
 *
 *  purpose:    CXMLException - класс исключения при ошибках XML.
 *  version:    1.0
 ************************************************************************/

#ifndef __XMLEXCEPTION_H__
#define __XMLEXCEPTION_H__

#include "Core.h"

#include "MyException.h"

// Исключение при работе с XML.
// Author: Kapralov A.
class CORE_API CXMLException : public CMyException
{
public:
    // Конструктор.
    CXMLException();
    // Конструктор.
    // _message - сообщение об ошибке.
    CXMLException(const char * _message);
    // Конструктор.
    // _message - сообщение об ошибке.
    CXMLException(CString & _message);
};

#endif // __XMLEXCEPTION_H__


