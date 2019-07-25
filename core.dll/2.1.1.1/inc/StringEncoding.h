/************************************************************************
 *  created:    25.2.2008  16:56
 *  filename:   StringEncoding.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __STRINGENCODING_H__
#define __STRINGENCODING_H__

#include "Core.h"

#include <string>
using std::string;

#define ENCODING_ACP "ACP"
#define ENCODING_UTF_8 "UTF-8"

CORE_API void ToUnicode(const char * _source, std::wstring & _wresult, UINT _sourceEnc);
CORE_API void FromUnicode(std::wstring &_sourceInUnicode, string &_result, UINT _resultEnc);
CORE_API void FromUnicode(std::wstring &_sourceInUnicode, CString &_result, UINT _resultEnc);

// Переводит строку в строку с требуемой кодировкой.
// _source - исходная строка.
// _result - результирующая строка.
// _sourceEnc - кодировка источника.
// _resultEnc - требуемая кодировка.
CORE_API bool Encode(const char * _source, string & _result, 
    const char *_sourceEnc, const char *_resultEnc);

// Переводит строку в строку с требуемой кодировкой.
// _source - исходная строка.
// _result - результирующая строка.
// _sourceEnc - кодировка источника.
// _resultEnc - требуемая кодировка.
CORE_API void Encode(const char * _source, string & _result, 
    UINT _sourceEnc, UINT _resultEnc);

/*CORE_API void Encode(const char * _source, CString & _result, 
    UINT _sourceEnc, UINT _resultEnc);*/

#endif // __STRINGENCODING_H__