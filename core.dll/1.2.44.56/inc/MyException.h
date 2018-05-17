/************************************************************************
 *  created:    18.7.2007  11:08
 *  filename:   MyException.h
 *  author:     Kapralov A.
 *
 *  purpose:    CMyException - ������� ����� ����������.
 *  version:    1.1
 ************************************************************************/

#ifndef __MYEXCEPTION_H__
#define __MYEXCEPTION_H__

// ������� ����� ����������.
// Author: Kapralov A.
class CMyException {
private:
  // ��� ������;
  DWORD m_errorCode;
  // ��������� �� ������.
  std::string m_message;

public:
  // ����������� �� ���������.
  CMyException() : m_errorCode(0) {}

  // �����������.
  // _message - ��������� �� ������.
  CMyException(const char * _message) :
      m_errorCode(0), m_message(_message) {}

    
  // �����������.
  // _message - ��������� �� ������.
  CMyException(DWORD errorCode, const char * _message) :
      m_errorCode(errorCode), m_message(_message) {}

public:
  // ���������� ��������� �� ������.
  inline DWORD GetErrorCode() const {
    return m_errorCode;
  }

  // ���������� ��������� �� ������.
  inline std::string GetMessage() const 
  {
      return m_message;      
  }
};

#endif // __MYEXCEPTION_H__


