/********************************************************************
  created:    3.2.2007   13:31
  filename:   Cookie.h
  author:     Kapralov A.
  
  purpose:    
  version:    1.0.1
  updated:    4.4.2007 20:58
*********************************************************************/

#ifndef __COOKIE_H__
#define __COOKIE_H__

#include "HttpLib.h"

//
// <KAE>
class HTTPLIB_API CCookie
{
public: // Construction/Destruction
  
  // Initial constructor
  CCookie(const char * _szName, const char * _szValue = NULL);
  // Initial constructor
  CCookie(const CString & _sName, const CString & _sValue);
  // Copy constructor
  CCookie(const CCookie & _Cookie);
  // Destructor
  virtual ~CCookie();

private:
  // Default constructor
  CCookie();
  CCookie & operator =(const CCookie & _Cookie);

public: // Operations

  // Converts cookie to string
  void ToString(CString & _String) const;

public: // Access

  // Sets cookie's value
  void SetValue(const char * _szValue);
  // Sets cookie's value
  void SetValue(const CString & _sValue);
  // Gets cookie's value
  const char * GetValue() const;
  // Gets cookie's name
  const char * GetName() const;

private: // Properties
  CString m_sName;
  CString m_sValue;
};

#endif // __COOKIE_H__