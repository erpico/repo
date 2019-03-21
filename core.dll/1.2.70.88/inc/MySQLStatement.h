/************************************************************************
*  created:    19.7.2007  11:21
*  filename:   MySQLStatement.h
*  author:     Kapralov A.
*
*  purpose:    CMySQLStatement - оператор.
*  version:    1.0
************************************************************************/

#ifndef __MYSQLSTATEMENT_H__
#define __MYSQLSTATEMENT_H__

#include "Core.h"

#include "MySQL.h"
#include "MySQLResultSet.h"

//
// Оператор.
// Author: Kapralov A.
class CORE_API CMySQLStatement
{
private:
  // Соединение с БД.
  CMySQL * m_pDBConnection;
  // Текущий набор данных.
  CMySQLResultSet * m_pResultSet;

private:
  // Конструктор по умолчанию.
  CMySQLStatement();
  // Конструктор копирования.
  CMySQLStatement(const CMySQLStatement & _anotherSatement);

public:
  // Конструктор.
  // _pDBConnection - Соединение с БД.
  CMySQLStatement(CMySQL * _pDBConnection);

public:
  // Деструктор.
  ~CMySQLStatement();

private:
  CMySQLStatement & operator =(const CMySQLStatement & _anotherSatement);

public:
  // Выполняет запрос к БД.
  void Execute(const char * _sql);
#ifndef DEBUG_MYSQL
  // Выполняет запрос к БД.
  // Возвращает: результирующий набор данных.
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

