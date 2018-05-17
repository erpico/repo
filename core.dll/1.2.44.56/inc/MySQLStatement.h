/************************************************************************
*  created:    19.7.2007  11:21
*  filename:   MySQLStatement.h
*  author:     Kapralov A.
*
*  purpose:    CMySQLStatement - ��������.
*  version:    1.0
************************************************************************/

#ifndef __MYSQLSTATEMENT_H__
#define __MYSQLSTATEMENT_H__

#include "Core.h"

#include "MySQL.h"
#include "MySQLResultSet.h"

//
// ��������.
// Author: Kapralov A.
class CORE_API CMySQLStatement
{
private:
  // ���������� � ��.
  CMySQL * m_pDBConnection;
  // ������� ����� ������.
  CMySQLResultSet * m_pResultSet;

private:
  // ����������� �� ���������.
  CMySQLStatement();
  // ����������� �����������.
  CMySQLStatement(const CMySQLStatement & _anotherSatement);

public:
  // �����������.
  // _pDBConnection - ���������� � ��.
  CMySQLStatement(CMySQL * _pDBConnection);

public:
  // ����������.
  ~CMySQLStatement();

private:
  CMySQLStatement & operator =(const CMySQLStatement & _anotherSatement);

public:
  // ��������� ������ � ��.
  void Execute(const char * _sql);
#ifndef DEBUG_MYSQL
  // ��������� ������ � ��.
  // ����������: �������������� ����� ������.
  CMySQLResultSet * ExecuteQuery(const char * _sql);
#else
  CMySQLResultSet * ExecuteQueryDbg(const char * _sql, const char * _strFile, int _iLine);
#endif

public:
  //
  unsigned long Insert(const char * _sql);
};

#ifdef DEBUG_MYSQL
  #define ExecuteQuery(x) ExecuteQueryDbg(x, __FILE__, __LINE__)
#endif

#endif // __MYSQLSTATEMENT_H__

