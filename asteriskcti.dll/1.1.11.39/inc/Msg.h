#pragma once
#include "ErpicoCTI/WCTI_Main.h"
#include <map>
#include <string>

#define _DECLSPEC_MSG __declspec( dllexport )

typedef std::map<std::string, std::string> CHeaderString; 

class _DECLSPEC_MSG CMsg
{
public:
  CMsg(void) : m_ActionID(0), length(2), m_str(0){};
  CMsg( char * msg ) : m_ActionID(0), length(2), m_str(0){ parseStr( msg );};
  CMsg( std::string str ) : m_ActionID(0), length(2), m_str(0){parseStr( str.c_str());};
  ~CMsg(void);

  void addHeader( const char * name, const char * value );
  void addActionID( WCTI_UINT actionID );
  const char * getHeader(const char * name );
  WCTI_UINT getActionID(){ return m_ActionID;};
  char * pack( size_t &len );
  char * packInLine( size_t &len );
  char* GetStr() { return m_str; }; // Возвращает когда то распарсенное сообщение, будьте уверены что это еще валидный указатель
private:
  int m_ActionID;
  void parseStr( const char * str );
  CHeaderString m_Headers;
  size_t length;
  char* m_str; // все сообщение
};
