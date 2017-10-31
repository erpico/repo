/*
 * AsteriskCTI.h
 * 
 *
 * Капралов А.
 * 14.2.2013 18:56
 */
#ifndef __ASTERISKCTI_H__
#define __ASTERISKCTI_H__

#ifdef ASTERISKCTI_EXPORTS
#define ASTERISKCTI_API __declspec(dllexport)
#else
#define ASTERISKCTI_API __declspec(dllimport)
#endif

#endif // __ASTERISKCTI_H__