/************************************************************************
*  created:    19.7.2007  11:13
*  filename:   MySQLResultSet.h
*  author:     Kapralov A.
*
*  purpose:    CMySQLResultSet - класс набора данных, результата 
*              выполнения запроса к БД.
*  version:    1.0
************************************************************************/

#ifndef __MYSQLRESULTSET_H__
#define __MYSQLRESULTSET_H__

#include "Core.h"

#include "MySQL.h"

// Набор данных, результат выполнения запроса к БД.
// Author: Kapralov A.
class CORE_API CMySQLResultSet
{
private:
  // Соединение с БД.
  CMySQL * m_pDBConnection;
  // Стандартный набор данных.
  MYSQL_RES * m_pRes;

private:
  // Текущий номер строки.
  int m_currentRowIndex;
  // Текущая строка.
  MYSQL_ROW m_currentRow;

private:
  friend class CMySQLStatement;

  //private:
public:
  // Конструктор по умолчанию.
  CMySQLResultSet();
  // Конструктор копирования.
  CMySQLResultSet(const CMySQLResultSet & _anotherResultSet);

  //protected:
  // Конструктор.
  // _pDBConnection - соединение с БД.
  // _pRes - набор данных.
  CMySQLResultSet(CMySQL * _pDBConnection, MYSQL_RES * _pRes);
public:
  // Деструктор.
  ~CMySQLResultSet();

private:
  CMySQLResultSet & operator =(const CMySQLResultSet & _anotherResultSet);

public:
  // Переходит к следующей строке.
  // Возвращает: true - если успешно, false - иначе.
  bool Next();

private:
  // Проверяет на валидность набор данных.
  void CheckResultSet();
  // Проверяет на корректность номер колонки.
  // _columnIndex - номер колонки. 
  void CheckColumnIndex(int _columnIndex);

public:
  // Возвращает true если в ячейке null, иначе fasle
  bool GetIsNull(int _columnIndex);

  // Возвращает значение ячейки типа short.
  // _columnIndex - номер колонки.
  short GetShort(int _columnIndex);
  // Возвращает значение ячейки типа int.
  // _columnIndex - номер колонки.
  int GetInt(int _columnIndex);
  // Возвращает значение ячейки типа long.
  // _columnIndex - номер колонки.
  long GetLong(int _columnIndex);
  // Возвращает значение ячейки типа unsigned int.
  // _columnIndex - номер колонки.
  unsigned int GetUnsignedInt(int _columnIndex);
  // Возвращает значение ячейки типа unsigned long.
  // _columnIndex - номер колонки.
  unsigned long GetUnsignedLong(int _columnIndex);
  // Возвращает значение ячейки типа char.
  // _columnIndex - номер колонки.
  char GetChar(int _columnIndex);
  // Возвращает значение ячейки типа float.
  // _columnIndex - номер колонки.
  float GetFloat(int _columnIndex);
  // Возвращает значение ячейки типа double.
  // _columnIndex - номер колонки.
  double GetDouble(int _columnIndex);
  // Возвращает значение ячейки типа const char * (массив из char).
  // _columnIndex - номер колонки.
  const char * GetCharArray(int _columnIndex);
  // Возвращает значение ячейки типа time_t
  // _columnIndex - номер колонки.
  time_t GetDateTime(int _columnIndex);
  // Возвращает значение ячейки типа bool.
  // _columnIndex - номер колонки.
  bool GetBool(int _columnIndex);

public:
  // Возвращает количество строк.
  unsigned __int64 GetRowCount();

  // Возвращает индекс поля по его названию, -1 если такого поля нет
  unsigned int GetFieldIndex(char *szFieldName);
};



#endif // __MYSQLRESULTSET_H__
