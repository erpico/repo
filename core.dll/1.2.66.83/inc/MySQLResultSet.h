/************************************************************************
*  created:    19.7.2007  11:13
*  filename:   MySQLResultSet.h
*  author:     Kapralov A.
*
*  purpose:    CMySQLResultSet - ����� ������ ������, ���������� 
*              ���������� ������� � ��.
*  version:    1.0
************************************************************************/

#ifndef __MYSQLRESULTSET_H__
#define __MYSQLRESULTSET_H__

#include "Core.h"

#include "MySQL.h"

// ����� ������, ��������� ���������� ������� � ��.
// Author: Kapralov A.
class CORE_API CMySQLResultSet
{
private:
  // ���������� � ��.
  CMySQL * m_pDBConnection;
  // ����������� ����� ������.
  MYSQL_RES * m_pRes;

private:
  // ������� ����� ������.
  int m_currentRowIndex;
  // ������� ������.
  MYSQL_ROW m_currentRow;

private:
  friend class CMySQLStatement;

  //private:
public:
  // ����������� �� ���������.
  CMySQLResultSet();
  // ����������� �����������.
  CMySQLResultSet(const CMySQLResultSet & _anotherResultSet);

  //protected:
  // �����������.
  // _pDBConnection - ���������� � ��.
  // _pRes - ����� ������.
  CMySQLResultSet(CMySQL * _pDBConnection, MYSQL_RES * _pRes);
public:
  // ����������.
  ~CMySQLResultSet();

private:
  CMySQLResultSet & operator =(const CMySQLResultSet & _anotherResultSet);

public:
  // ��������� � ��������� ������.
  // ����������: true - ���� �������, false - �����.
  bool Next();

private:
  // ��������� �� ���������� ����� ������.
  void CheckResultSet();
  // ��������� �� ������������ ����� �������.
  // _columnIndex - ����� �������. 
  void CheckColumnIndex(int _columnIndex);

public:
  // ���������� true ���� � ������ null, ����� fasle
  bool GetIsNull(int _columnIndex);

  // ���������� �������� ������ ���� short.
  // _columnIndex - ����� �������.
  short GetShort(int _columnIndex);
  // ���������� �������� ������ ���� int.
  // _columnIndex - ����� �������.
  int GetInt(int _columnIndex);
  // ���������� �������� ������ ���� long.
  // _columnIndex - ����� �������.
  long GetLong(int _columnIndex);
  // ���������� �������� ������ ���� unsigned int.
  // _columnIndex - ����� �������.
  unsigned int GetUnsignedInt(int _columnIndex);
  // ���������� �������� ������ ���� unsigned long.
  // _columnIndex - ����� �������.
  unsigned long GetUnsignedLong(int _columnIndex);
  // ���������� �������� ������ ���� char.
  // _columnIndex - ����� �������.
  char GetChar(int _columnIndex);
  // ���������� �������� ������ ���� float.
  // _columnIndex - ����� �������.
  float GetFloat(int _columnIndex);
  // ���������� �������� ������ ���� double.
  // _columnIndex - ����� �������.
  double GetDouble(int _columnIndex);
  // ���������� �������� ������ ���� const char * (������ �� char).
  // _columnIndex - ����� �������.
  const char * GetCharArray(int _columnIndex);
  // ���������� �������� ������ ���� time_t
  // _columnIndex - ����� �������.
  time_t GetDateTime(int _columnIndex);
  // ���������� �������� ������ ���� bool.
  // _columnIndex - ����� �������.
  bool GetBool(int _columnIndex);

public:
  // ���������� ���������� �����.
  unsigned __int64 GetRowCount();

  // ���������� ������ ���� �� ��� ��������, -1 ���� ������ ���� ���
  unsigned int GetFieldIndex(char *szFieldName);
};



#endif // __MYSQLRESULTSET_H__
