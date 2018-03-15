/*
 * Core.h
 * 
 *
 * Капралов А.
 * 8.2.2013 12:49
 */

#ifndef __CORE_H__
#define __CORE_H__

#ifdef CORE_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>

class CORE_API CTranslator;

CORE_API void dummy();

CORE_API bool approximatelyEqual(double a, double b, double epsilon);

CORE_API bool essentiallyEqual(double a, double b, double epsilon);

CORE_API bool definitelyGreaterThan(double a, double b, double epsilon);

CORE_API bool definitelyLessThan(double a, double b, double epsilon);

CORE_API const char*    Translate(const char* x);
CORE_API std::wstring   Translate(const wchar_t* x);
CORE_API CTranslator&   GetTranslator();

#define _(x) Translate(x)

#endif // __CORE_H__