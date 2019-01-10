/************************************************************************
*  created:    18.7.2007  11:05
*  filename:   SQLException.h
*  author:     Kapralov A.
*
*  purpose:    CSQLException - класс исключения при использовании БД.
*  version:    1.0
************************************************************************/

#ifndef __SQLEXCEPTION_H__
#define __SQLEXCEPTION_H__

#include "Core.h"

#include "MyException.h"

// Исключение при использовании БД.
// Author: Kapralov A.
class CORE_API CSQLException : public CMyException
{
public:
  // Конструктор.
  CSQLException();
  // Конструктор.
  // _message - сообщение об ошибке.
  CSQLException(const char * _message);
  // Конструктор.
  // _message - сообщение об ошибке.
  CSQLException(std::string & _message);
};

#endif // __SQLEXCEPTION_H__


