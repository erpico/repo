/************************************************************************
 *  created:    18.7.2007  11:08
 *  filename:   MyException.h
 *  author:     Kapralov A.
 *
 *  purpose:    CMyException - базовый класс исключений.
 *  version:    1.1
 ************************************************************************/

#ifndef __MYEXCEPTION_H__
#define __MYEXCEPTION_H__

// Базовый класс исключений.
// Author: Kapralov A.
class CMyException {
private:
  // Код ошибки;
  DWORD m_errorCode;
  // Сообщение об ошибке.
  std::string m_message;

public:
  // Конструктор по умолчанию.
  CMyException() : m_errorCode(0) {}

  // Конструктор.
  // _message - сообщение об ошибке.
  CMyException(const char * _message) :
      m_errorCode(0), m_message(_message) {}

    
  // Конструктор.
  // _message - сообщение об ошибке.
  CMyException(DWORD errorCode, const char * _message) :
      m_errorCode(errorCode), m_message(_message) {}

public:
  // Возвращает сообщение об ошибке.
  inline DWORD GetErrorCode() const {
    return m_errorCode;
  }

  // Возвращает сообщение об ошибке.
  inline std::string GetMessage() const 
  {
      return m_message;      
  }
};

#endif // __MYEXCEPTION_H__


