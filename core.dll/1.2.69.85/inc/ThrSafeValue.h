#pragma once

//////////////////////////////////////////////////////////////////////////
// ѕотокобезопасные простые переменные

template <typename T>
class SafeVar
{
  T m_val;
  CCriticalSection m_cs;

public:
  SafeVar() {};
  ~SafeVar() {};

  T get() {
    T ret;
    CSingleLock _cs(&m_cs, TRUE);
    ret = m_val;
    return ret;
  }

  void set(const T& val) {
    CSingleLock _cs(&m_cs, TRUE);
    m_val = val;
  }

  operator T() { 
    return get(); 
  }

  T operator =(const T& val) {
    set(val);
    return get();
  }

  bool operator ==(const T& val) const {
    return m_val == val;
  }

  bool operator !=(const T& val) const {
    return m_val != val;
  }

  T& operator ->() {
    return m_val;
  }

};

typedef SafeVar<bool> SafeBool;
typedef SafeVar<int> SafeInt;
typedef SafeVar<DWORD> SafeDWORD;
typedef SafeVar<CString> SafeString;
typedef SafeVar<INT_PTR> Safe_INT_PTR;
typedef SafeVar<double> SafeDouble;

//////////////////////////////////////////////////////////////////////////