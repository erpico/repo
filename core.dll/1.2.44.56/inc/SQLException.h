/************************************************************************
*  created:    18.7.2007  11:05
*  filename:   SQLException.h
*  author:     Kapralov A.
*
*  purpose:    CSQLException - ����� ���������� ��� ������������� ��.
*  version:    1.0
************************************************************************/

#ifndef __SQLEXCEPTION_H__
#define __SQLEXCEPTION_H__

#include "Core.h"

#include "MyException.h"

// ���������� ��� ������������� ��.
// Author: Kapralov A.
class CORE_API CSQLException : public CMyException
{
public:
  // �����������.
  CSQLException();
  // �����������.
  // _message - ��������� �� ������.
  CSQLException(const char * _message);
  // �����������.
  // _message - ��������� �� ������.
  CSQLException(std::string & _message);
};

#endif // __SQLEXCEPTION_H__


